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
    _length = sizeof(_tune) / sizeof(int);
}

int NGJingleSuperMarioShort::getDefaultTempo() {
    return 120;
}

int NGJingleSuperMarioShort::getTune() {
    int res = NO_NOTE;
    if (_indexTune < _length) {
        res = _tune[_indexTune];
        _indexTune++;
    }
    return res;
}

int NGJingleSuperMarioShort::getBeat() {
    int res = NO_NOTE;
    if (_indexBeat < _length) {
        res = _beat[_indexBeat];
        _indexBeat++;
    }
    return res;
}
