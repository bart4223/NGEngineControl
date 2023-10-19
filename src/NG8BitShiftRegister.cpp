//
//  NG8BitShiftRegister.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 17.10.23.
//

#include "NG8BitShiftRegister.h"

NG8BitShiftRegister::NG8BitShiftRegister(byte latchPin, byte clockPin, byte dataPin) {
    _create(latchPin, clockPin, dataPin);
}

void NG8BitShiftRegister::_create(byte latchPin, byte clockPin, byte dataPin) {
    _latchPin = latchPin;
    _clockPin = clockPin;
    _dataPin = dataPin;
}

void NG8BitShiftRegister::_processingValue() {
    digitalWrite(_latchPin, LOW);
    shiftOut(_dataPin, _clockPin, MSBFIRST, _value);
    digitalWrite(_latchPin, HIGH);
}

void NG8BitShiftRegister::initialize() {
    pinMode(_latchPin, OUTPUT);
    digitalWrite(_latchPin, LOW);
    pinMode(_clockPin, OUTPUT);
    digitalWrite(_clockPin, LOW);
    pinMode(_dataPin, OUTPUT);
    digitalWrite(_dataPin, LOW);
}

void NG8BitShiftRegister::setValue(byte value) {
    _value = value;
    _processingValue();
}

byte NG8BitShiftRegister::getValue() {
    return _value;
}

void NG8BitShiftRegister::shiftValue() {
    shiftValue(srdLeft);
}

void NG8BitShiftRegister::shiftValue(shiftRegisterDirection direction) {
    switch(direction) {
        case srdLeft:
            setValue(_value << 1);
            break;
        case srdRight:
            setValue(_value >> 1);
            break;
    }
}
