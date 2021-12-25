//
//  NGJingleChristmasSong.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.12.21.
//

#include "NGJingleChristmasSong.h"

NGJingleChristmasSong::NGJingleChristmasSong() {
    _create();
}

void NGJingleChristmasSong::_create() {
    NGCustomJingle::_create();
    _tuneRef = &_tune[0];
    _beatRef = &_beat[0];
    _length = sizeof(_tune) / sizeof(_beat[0]);
    _defaultTempo = 160;
}
