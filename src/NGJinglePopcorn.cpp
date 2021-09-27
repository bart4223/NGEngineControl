//
//  NGJinglePopcorn.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.09.21.
//

#include "NGJinglePopcorn.h"

NGJinglePopcorn::NGJinglePopcorn() {
    _create();
}

void NGJinglePopcorn::_create() {
    NGCustomJingle::_create();
    _tuneRef = &_tune[0];
    _beatRef = &_beat[0];
    _length = sizeof(_tune) / sizeof(_beat[0]);
    _defaultTempo = 190;
}
