//
//  NGSoundMachine.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.09.21.
//

#include "NGCustomJingle.h"
#include "NGSoundMachine.h"

NGSoundMachine::NGSoundMachine() {
    _create(DEFPINPIEZO, NOACTIVATIONPIN);
}

NGSoundMachine::NGSoundMachine(int pinPiezo) {
    _create(pinPiezo, NOACTIVATIONPIN);
}

NGSoundMachine::NGSoundMachine(int pinPiezo, int pinActivation) {
    _create(pinPiezo, pinActivation);
}

void NGSoundMachine::_create(int pinPiezo, int pinActivation) {
    _pinPiezo = pinPiezo;
    _pinActivation = pinActivation;
}

void NGSoundMachine::initialize() {
    pinMode(_pinPiezo, OUTPUT);
    if (hasActivationPin()) {
        pinMode(_pinActivation, OUTPUT);
        digitalWrite(_pinActivation, LOW);
    }
}

void NGSoundMachine::activate() {
    if (hasActivationPin()) {
        digitalWrite(_pinActivation, HIGH);
    }
}

void NGSoundMachine::deactivate() {
    if (hasActivationPin()) {
        digitalWrite(_pinActivation, LOW);
    }
}

bool NGSoundMachine::hasActivationPin() {
    return _pinActivation != NOACTIVATIONPIN;
}

int NGSoundMachine::registerJingle(NGCustomJingle *jingle) {
    byte res = _jingleCount;
    _jingles[_jingleCount] = jingle;
    _jingleCount++;
    return res;
}

void NGSoundMachine::playRandom() {
    if (_jingleCount > 0) {
        play(random(0, _jingleCount));
    }
}

void NGSoundMachine::playRandom(int tempo) {
    if (_jingleCount > 0) {
        play(random(0, _jingleCount), tempo);
    }
}

void NGSoundMachine::play(byte jingle) {
    play(jingle, getDefaultTempo(jingle));
}

void NGSoundMachine::play(byte jingle, int tempo) {
    _currentJingle = jingle;
    _currentTempo = tempo;
    _jingles[_currentJingle]->reset();
    if (!_concurrently) {
        while(_jingles[_currentJingle]->hasTune()) {
            _currentTune = _jingles[_currentJingle]->getTune();
            _currentBeat = _jingles[_currentJingle]->getBeat();
            if (_currentTune == NO_NOTE) {
                noTone(_pinPiezo);
            } else {
                tone(_pinPiezo, _currentTune, _currentBeat * _currentTempo);
            }
            delay(_currentBeat * _currentTempo + _currentTempo / 10);
        }
        _currentJingle = NOCURRENTJINGLE;
    } else {
        _currentTune = NOCURRENTTUNE;
        _currentBeat = 0;
    }
}

int NGSoundMachine::getJingleCount() {
    return _jingleCount;
}

int NGSoundMachine::getMaxJingleCount() {
    return MAXJINGLES;
}

int NGSoundMachine::getDefaultTempo(byte jingle) {
    return _jingles[jingle]->getDefaultTempo();
}

void NGSoundMachine::setConcurrently(bool concurrently) {
    _concurrently = concurrently;
}

bool NGSoundMachine::getConcurrently() {
    return _concurrently;
}

bool NGSoundMachine::hasCurrentJingle() {
    return _currentJingle != NOCURRENTJINGLE;
}

void NGSoundMachine::processingLoop() {
    if (getConcurrently() && hasCurrentJingle()) {
        if (_currentTune == NOCURRENTTUNE) {
            if (_jingles[_currentJingle]->hasTune()) {
                _currentTune = _jingles[_currentJingle]->getTune();
                _currentBeat = _jingles[_currentJingle]->getBeat();
                if (_currentTune == NO_NOTE) {
                    noTone(_pinPiezo);
                } else {
                    tone(_pinPiezo, _currentTune, _currentBeat * _currentTempo);
                }
                _currentDelay = _currentBeat * _currentTempo + _currentTempo / 10;
                _lastTune = millis();
            } else {
                _currentTune = NOCURRENTTUNE;
                _currentJingle = NOCURRENTJINGLE;
            }
        } else if (millis() - _lastTune >= _currentDelay) {
            _currentTune = NOCURRENTTUNE;
        }
    }
}
