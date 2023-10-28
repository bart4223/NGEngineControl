//
//  NG7SegmentDisplay.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 20.10.23.
//

#include "NG7SegmentDisplay.h"

NG7SegmentDisplay::NG7SegmentDisplay(byte latchPin, byte clockPin, byte dataPin) {
    _create(latchPin, clockPin, dataPin);
}

void NG7SegmentDisplay::_create(byte latchPin, byte clockPin, byte dataPin) {
    _shiftRegister = new NG8BitShiftRegister(latchPin, clockPin, dataPin);
}

byte NG7SegmentDisplay::_getThreshold() {
    byte res = 9;
    if (_mode == ssmHex) {
        res = 15;
    }
    return res;
}

void NG7SegmentDisplay::initialize() {
    _shiftRegister->initialize();
}

byte NG7SegmentDisplay::getValue() {
    return _value;
}

void NG7SegmentDisplay::setValue(byte value) {
    _value = value;
    switch(value) {
        case 0:
            _shiftRegister->setValue(63);
            break;
        case 1:
            _shiftRegister->setValue(6);
            break;
        case 2:
            _shiftRegister->setValue(91);
            break;
        case 3:
            _shiftRegister->setValue(79);
            break;
        case 4:
            _shiftRegister->setValue(102);
            break;
        case 5:
            _shiftRegister->setValue(109);
            break;
        case 6:
            _shiftRegister->setValue(125);
            break;
        case 7:
            _shiftRegister->setValue(7);
            break;
        case 8:
            _shiftRegister->setValue(127);
            break;
        case 9:
            _shiftRegister->setValue(111);
            break;
        case 10:
            _shiftRegister->setValue(119);
            break;
        case 11:
            _shiftRegister->setValue(127);
            break;
        case 12:
            _shiftRegister->setValue(57);
            break;
        case 13:
            _shiftRegister->setValue(63);
            break;
        case 14:
            _shiftRegister->setValue(121);
            break;
        case 15:
            _shiftRegister->setValue(113);
            break;
    }
}

void NG7SegmentDisplay::incrementValue() {
    byte threshold = _getThreshold();
    byte value = _value;
    value++;
    if (value > threshold) {
        value = 0;
    }
    setValue(value);
}

void NG7SegmentDisplay::decrementValue() {
    byte threshold = _getThreshold();
    byte value = _value;
    if (value == 0) {
        value = threshold;
    } else {
        value--;
    }
    setValue(value);
}

void NG7SegmentDisplay::setMode(sevenSegmentMode mode) {
    _mode = mode;
}

void NG7SegmentDisplay::setDot() {
    _shiftRegister->setValue(_shiftRegister->getValue() + 128);
}

void NG7SegmentDisplay::resetDot() {
    _shiftRegister->setValue(_shiftRegister->getValue() - 128);
}

void NG7SegmentDisplay::beginUpdate() {
    _shiftRegister->beginUpdate();
}

void NG7SegmentDisplay::endUpdate() {
    _shiftRegister->endUpdate();
}
