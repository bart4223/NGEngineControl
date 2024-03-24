//
//  NGMulti7SegmentDisplay.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 24.03.24.
//

#include "NGMulti7SegmentDisplay.h"

NGMulti7SegmentDisplay::NGMulti7SegmentDisplay(byte latchPin, byte clockPin, byte dataPin, byte digitcount) {
    _create(latchPin, clockPin, dataPin, digitcount);
}

void NGMulti7SegmentDisplay::_create(byte latchPin, byte clockPin, byte dataPin, byte digitcount) {
    _digitcount = digitcount;
    _digit = new NG7SegmentDisplay(latchPin, clockPin, dataPin);
}

int NGMulti7SegmentDisplay::_getBaseFromMode() {
    int res = 0;
    switch(_digit->getMode()) {
        case ssmDec:
            res = 10;
            break;
        case ssmHex:
            res = 16;
            break;
    }
    return res;
}

void NGMulti7SegmentDisplay::initialize() {
    _digit->initialize();
}

void NGMulti7SegmentDisplay::setMode(sevenSegmentMode mode) {
    _digit->setMode(mode);
}

void NGMulti7SegmentDisplay::setValue(int value) {
    _value = value;
    int base = _getBaseFromMode();
    for (int i = _digitcount - 1; i > 0; i--) {
        int digitvalue = _value / pow(base, i);
        _digit->setValue(digitvalue);
    }
    _digit->setValue(_value % base);
}

void NGMulti7SegmentDisplay::incrementValue() {
    int value = _value;
    value++;
    if (value >= pow(_getBaseFromMode(), _digitcount)) {
        value = 0;
    }
    setValue(value);
}

void NGMulti7SegmentDisplay::decrementValue() {
    int value = _value;
    value--;
    if (value < 0) {
        value = pow(_getBaseFromMode(), _digitcount);
    }
    setValue(value);
}
