//
//  NGMorseToneNotification.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 16.01.22.
//

#include "NGMorseToneNotification.h"
#include <NGJingleMorseDit.h>
#include <NGJingleMorseDah.h>
#include <NGJingleMorseBreakLetter.h>
#include <NGJingleMorseBreakWord.h>

NGMorseToneNotification::NGMorseToneNotification() {
    _create(DEFPINPIEZO, DEFTEMPO);
}

NGMorseToneNotification::NGMorseToneNotification(int pinPiezo) {
    _create(pinPiezo, DEFTEMPO);
}

NGMorseToneNotification::NGMorseToneNotification(int pinPiezo, int tempo) {
    _create(pinPiezo, tempo);
}

void NGMorseToneNotification::_create(int pinPiezo, int tempo) {
    if (pinPiezo == DEFPINPIEZO) {
        _morseToneGenerator = new NGMorseToneGenerator();
    } else {
        _morseToneGenerator = new NGMorseToneGenerator(pinPiezo);
    }
    if (tempo != DEFTEMPO) {
        _morseToneGenerator->setTempo(tempo);
    }
}

void NGMorseToneNotification::_playInfo(char *info) {
    if (_playAllInfos) {
        _morseToneGenerator->play(info);
    } else {
        // play text between #
        int x = -1;
        char word[100];
        for (int i = 0; i < strlen(info); i++) {
            if (info[i] == '#') {
                if (x < 0) {
                    x++;
                } else {
                    word[x] = '\0';
                    _morseToneGenerator->play(word);
                    x = -1;
                }
            } else if (x >= 0) {
                word[x] = info[i];
                x++;
            }
        }
    }
}

void NGMorseToneNotification::initialize() {
    if (!_morseToneGenerator->hasJingleDit()) {
        _morseToneGenerator->registerJingleDit(new NGJingleMorseDit);
    }
    if (!_morseToneGenerator->hasJingleDah()) {
        _morseToneGenerator->registerJingleDah(new NGJingleMorseDah);
    }
    if (!_morseToneGenerator->hasJingleBreakLetter()) {
        _morseToneGenerator->registerJingleBreakLetter(new NGJingleMorseBreakLetter);
    }
    if (!_morseToneGenerator->hasJingleBreakWord()) {
        _morseToneGenerator->registerJingleBreakWord(new NGJingleMorseBreakWord);
    }
    _morseToneGenerator->initialize();
}

void NGMorseToneNotification::registerJingleDit(NGCustomJingle *jingle) {
    _morseToneGenerator->registerJingleDit(jingle);
}

void NGMorseToneNotification::registerJingleDah(NGCustomJingle *jingle) {
    _morseToneGenerator->registerJingleDah(jingle);
}

void NGMorseToneNotification::registerJingleBreakLetter(NGCustomJingle *jingle) {
    _morseToneGenerator->registerJingleBreakLetter(jingle);
}

void NGMorseToneNotification::registerJingleBreakWord(NGCustomJingle *jingle) {
    _morseToneGenerator->registerJingleBreakWord(jingle);
}

char* NGMorseToneNotification::getName() {
    return (char*)"MorseTone";
}

void NGMorseToneNotification::clear() {
    //nop
}

void NGMorseToneNotification::clear(int line) {
    //nop
}

void NGMorseToneNotification::writeInfo(char* info) {
    _playInfo(info);
}

void NGMorseToneNotification::writeInfo(char* info, int line) {
    _playInfo(info);
}

void NGMorseToneNotification::writeInfo(char* info, int line, int column) {
    _playInfo(info);
}

void NGMorseToneNotification::setPlayAllInfos(bool playAllInfos) {
    _playAllInfos = playAllInfos;
}
