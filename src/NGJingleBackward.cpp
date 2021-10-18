//
//  NGJingleBackward.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 18.10.21.
//

#include "NGJingleBackward.h"

NGJingleBackward::NGJingleBackward() {
    _create();
}

void NGJingleBackward::_create() {
    NGCustomJingle::_create();
    _tuneRef = &_tune[0];
    _beatRef = &_beat[0];
    _length = sizeof(_tune) / sizeof(_beat[0]);
    _defaultTempo = 110;
}
