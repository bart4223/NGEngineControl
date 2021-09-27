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
    _length = sizeof(_tune) / sizeof(int);
}

int NGJingleSuperMario::getDefaultTempo() {
    return 120;
}

int NGJingleSuperMario::getTune() {
    int res = NO_NOTE;
    if (_indexTune < _length) {
        res = _tune[_indexTune];
        _indexTune++;
    }
    return res;
}

int NGJingleSuperMario::getBeat() {
    int res = NO_NOTE;
    if (_indexBeat < _length) {
        res = _beat[_indexBeat];
        _indexBeat++;
    }
    return res;
}

