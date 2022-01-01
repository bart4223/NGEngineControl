//
//  NGJingleMorseBreakLetter.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 01.01.22.
//

#include "NGJingleMorseBreakLetter.h"

NGJingleMorseBreakLetter::NGJingleMorseBreakLetter() {
    _create();
}

void NGJingleMorseBreakLetter::_create() {
    NGCustomJingle::_create();
    _tuneRef = &_tune[0];
    _beatRef = &_beat[0];
    _length = sizeof(_tune) / sizeof(_beat[0]);
    _defaultTempo = 100;
}
