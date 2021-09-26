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
    _length = 6;
}

int NGJingleHelloDude::getDefaultTempo() {
    return 120;
}

int NGJingleHelloDude::getTune() {
    int res = NO_NOTE;
    if (_indexTune < _length) {
        res = _tune[_indexTune];
        _indexTune++;
    }
    return res;
}

int NGJingleHelloDude::getBeat() {
    int res = NO_NOTE;
    if (_indexBeat < _length) {
        res = _beat[_indexBeat];
        _indexBeat++;
    }
    return res;
}

