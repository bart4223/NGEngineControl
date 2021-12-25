//
//  NGJingleJingleBells.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.12.21.
//

#include "NGJingleJingleBells.h"

NGJingleJingleBells::NGJingleJingleBells() {
    _create();
}

void NGJingleJingleBells::_create() {
    NGCustomJingle::_create();
    _tuneRef = &_tune[0];
    _beatRef = &_beat[0];
    _length = sizeof(_tune) / sizeof(_beat[0]);
    _defaultTempo = 160;
}
