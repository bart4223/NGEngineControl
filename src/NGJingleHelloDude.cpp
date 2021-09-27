//
//  NGJingleHelloDude.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 26.09.21.
//

#include "NGJingleHelloDude.h"

NGJingleHelloDude::NGJingleHelloDude() {
    _create();
}

void NGJingleHelloDude::_create() {
    NGCustomJingle::_create();
    _tuneRef = &_tune[0];
    _beatRef = &_beat[0];
    _length = sizeof(_tune) / sizeof(int);
}

int NGJingleHelloDude::getDefaultTempo() {
    return 120;
}

