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
    _length = sizeof(_tune) / sizeof(int);
}

int NGJingleAlarm::getDefaultTempo() {
    return 110;
}

int NGJingleAlarm::getTune() {
    int res = NO_NOTE;
    if (_indexTune < _length) {
        res = _tune[_indexTune];
        _indexTune++;
    }
    return res;
}

int NGJingleAlarm::getBeat() {
    int res = NO_NOTE;
    if (_indexBeat < _length) {
        res = _beat[_indexBeat];
        _indexBeat++;
    }
    return res;
}
