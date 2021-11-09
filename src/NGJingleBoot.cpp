//
//  NGJingleBoot.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.11.21.
//

#include "NGJingleBoot.h"

NGJingleBoot::NGJingleBoot() {
    _create();
}

void NGJingleBoot::_create() {
    NGCustomJingle::_create();
    _tuneRef = &_tune[0];
    _beatRef = &_beat[0];
    _length = sizeof(_tune) / sizeof(_beat[0]);
    _defaultTempo = 120;
}
