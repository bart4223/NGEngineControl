//
//  NGCustomJingle.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.09.21.
//

#include "NGCustomJingle.h"

void NGCustomJingle::_create() {
    reset();
    _length = 0;
}

void NGCustomJingle::reset() {
    _indexTune = 0;
    _indexBeat = 0;
}

bool NGCustomJingle::hasTune() {
    return _indexTune < _length;
}

int NGCustomJingle::getTune() {
    int res = NO_NOTE;
    if (_indexTune < _length) {
        res = *(_tuneRef + _indexTune);
        _indexTune++;
    }
    return res;
}

int NGCustomJingle::getBeat() {
    int res = NO_NOTE;
    if (_indexBeat < _length) {
        res = *(_beatRef + _indexBeat);
        _indexBeat++;
    }
    return res;
}
