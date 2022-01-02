//
//  NGSoundMachine.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.09.21.
//

#include "NGCustomJingle.h"
#include "NGSoundMachine.h"

NGSoundMachine::NGSoundMachine() {
    _create(DEFPINPIEZO);
}

NGSoundMachine::NGSoundMachine(int pinPiezo) {
    _create(pinPiezo);
}

void NGSoundMachine::_create(int pinPiezo) {
    _pinPiezo = pinPiezo;
}

void NGSoundMachine::initialize() {
    pinMode(_pinPiezo, OUTPUT);
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
    _jingles[jingle]->reset();
    while(_jingles[jingle]->hasTune()) {
        int tune = _jingles[jingle]->getTune();
        int beat = _jingles[jingle]->getBeat();
        if (tune == NO_NOTE) {
            noTone(_pinPiezo);
        } else {
            tone(_pinPiezo, tune, beat * tempo);
        }
        delay(beat * tempo);
        delay(tempo / 10);
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
