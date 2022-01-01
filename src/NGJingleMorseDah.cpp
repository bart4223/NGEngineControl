//
//  NGMorseDah.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 31.12.21.
//

#include "NGJingleMorseDah.h"

NGJingleMorseDah::NGJingleMorseDah() {
    _create();
}

void NGJingleMorseDah::_create() {
    NGCustomJingle::_create();
    _tuneRef = &_tune[0];
    _beatRef = &_beat[0];
    _length = sizeof(_tune) / sizeof(_beat[0]);
    _defaultTempo = 100;
}
