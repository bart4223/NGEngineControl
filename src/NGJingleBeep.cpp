//
//  NGJingleBeep.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 19.12.21.
//

#include "NGJingleBeep.h"

NGJingleBeep::NGJingleBeep() {
    _create();
}

void NGJingleBeep::_create() {
    NGCustomJingle::_create();
    _tuneRef = &_tune[0];
    _beatRef = &_beat[0];
    _length = sizeof(_tune) / sizeof(_beat[0]);
    _defaultTempo = 120;
}
