//
//  NGJingleGorilla.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.09.21.
//

#include "NGJingleGorilla.h"

NGJingleGorilla::NGJingleGorilla() {
    _create();
}

void NGJingleGorilla::_create() {
    NGCustomJingle::_create();
    _length = 12;
}

int NGJingleGorilla::getDefaultTempo() {
    return 170;
}

int NGJingleGorilla::getTune() {
    int res = NO_NOTE;
    if (_indexTune < _length) {
        res = _tune[_indexTune];
        _indexTune++;
    }
    return res;
}

int NGJingleGorilla::getBeat() {
    int res = NO_NOTE;
    if (_indexBeat < _length) {
        res = _beat[_indexBeat];
        _indexBeat++;
    }
    return res;
}
