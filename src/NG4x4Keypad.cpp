//
//  NG4x4Keypad.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 10.02.24.
//

#include "NG4x4Keypad.h"

NG4x4Keypad::NG4x4Keypad(byte pinRow0, byte pinRow1, byte pinRow2, byte pinRow3, byte pinCol0, byte pinCol1, byte pinCol2, byte pinCol3) {
    _create(pinRow0, pinRow1, pinRow2, pinRow3, pinCol0, pinCol1, pinCol2, pinCol3);
}

void NG4x4Keypad::_create(byte pinRow0, byte pinRow1, byte pinRow2, byte pinRow3, byte pinCol0, byte pinCol1, byte pinCol2, byte pinCol3) {
    _rowPins[0] = pinRow0;
    _rowPins[1] = pinRow1;
    _rowPins[2] = pinRow2;
    _rowPins[3] = pinRow3;
    _colPins[0] = pinCol0;
    _colPins[1] = pinCol1;
    _colPins[2] = pinCol2;
    _colPins[3] = pinCol3;
}

void NG4x4Keypad::registerCallback(FourxFourKeypadCallbackFunc callback) {
    _callback = callback;
}

void NG4x4Keypad::registerKey(byte row, byte col, char key) {
    if (row >= 0 && row < KEYPADROWS && col >= 0 && col < KEYPADCOLS) {
        _keys[row][col] = key;
    }
}

void NG4x4Keypad::setLogging(bool logging) {
    _logging = logging;
}

void NG4x4Keypad::initialize() {
    _keypad = new Keypad(makeKeymap(_keys), _rowPins, _colPins, KEYPADROWS, KEYPADCOLS);
}

void NG4x4Keypad::processingLoop() {
    char key = _keypad->getKey();
    if (key != NO_KEY){
        if (_logging) {
            Serial.println(key);
        }
        if (_callback != nullptr) {
            _callback(key);
        }
    }
}
