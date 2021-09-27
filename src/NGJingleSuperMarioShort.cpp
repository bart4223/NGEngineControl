//
//  NGJingleSuperMarioShort.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 26.09.21.
//

#include "NGJingleSuperMarioShort.h"

NGJingleSuperMarioShort::NGJingleSuperMarioShort() {
    _create();
}

void NGJingleSuperMarioShort::_create() {
    NGCustomJingle::_create();
    _tuneRef = &_tune[0];
    _beatRef = &_beat[0];
    _length = sizeof(_tune) / sizeof(int);
}

int NGJingleSuperMarioShort::getDefaultTempo() {
    return 120;
}
