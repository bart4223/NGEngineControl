//
//  NGJingleMorseBreakWord.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 01.01.22.
//

#include "NGJingleMorseBreakWord.h"

NGJingleMorseBreakWord::NGJingleMorseBreakWord() {
    _create();
}

void NGJingleMorseBreakWord::_create() {
    NGCustomJingle::_create();
    _tuneRef = &_tune[0];
    _beatRef = &_beat[0];
    _length = sizeof(_tune) / sizeof(_beat[0]);
    _defaultTempo = 100;
}
