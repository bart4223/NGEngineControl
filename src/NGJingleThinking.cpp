//
//  NGJingleThinking.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 28.10.21.
//

#include "NGJingleThinking.h"

NGJingleThinking::NGJingleThinking() {
    _create();
}

void NGJingleThinking::_create() {
    NGCustomJingle::_create();
    _tuneRef = &_tune[0];
    _beatRef = &_beat[0];
    _length = sizeof(_tune) / sizeof(_beat[0]);
    _defaultTempo = 100;
}

