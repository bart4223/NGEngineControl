//
//  NGJingleSuperMario.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.09.21.
//

#include "NGJingleSuperMario.h"

NGJingleSuperMario::NGJingleSuperMario() {
    _create();
}

void NGJingleSuperMario::_create() {
    NGCustomJingle::_create();
    _tuneRef = &_tune[0];
    _beatRef = &_beat[0];
    _length = sizeof(_tune) / sizeof(_beat[0]);
    _defaultTempo = 120;
}
