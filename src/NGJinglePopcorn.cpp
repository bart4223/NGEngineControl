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
    _length = 64;
}

int NGJinglePopcorn::getDefaultTempo() {
    return 190;
}

int NGJinglePopcorn::getTune() {
    int res = NO_NOTE;
    if (_indexTune < _length) {
        res = _tune[_indexTune];
        _indexTune++;
    }
    return res;
}

int NGJinglePopcorn::getBeat() {
    int res = NO_NOTE;
    if (_indexBeat < _length) {
        res = _beat[_indexBeat];
        _indexBeat++;
    }
    return res;
}
