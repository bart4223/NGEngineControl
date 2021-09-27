//
//  NGJingleAlarm.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 26.09.21.
//

#include "NGJingleAlarm.h"

NGJingleAlarm::NGJingleAlarm() {
    _create();
}

void NGJingleAlarm::_create() {
    NGCustomJingle::_create();
    _tuneRef = &_tune[0];
    _beatRef = &_beat[0];
    _length = sizeof(_tune) / sizeof(int);
}

int NGJingleAlarm::getDefaultTempo() {
    return 110;
}
