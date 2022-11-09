//
//  NGSimpleKeypad.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 08.11.22.
//

#include "NGSimpleKeypad.h"

NGSimpleKeypad::NGSimpleKeypad() {
    _create();
}

void NGSimpleKeypad::_create() {
    
}

void NGSimpleKeypad::registerCallback(simpleKeypadCallbackFunc callback) {
    _callback = callback;
}

void NGSimpleKeypad::registerKey(byte pin, byte id, int delay) {
    simpleKeypadData key;
    key.pin = pin;
    key.id = id;
    key.delay = delay;
    _keys[_keyCount] = key;
    _keyCount++;
}

void NGSimpleKeypad::initialize() {
    for (int i = 0; i < _keyCount; i++) {
        pinMode(_keys[i].pin, INPUT_PULLUP);
    }
}

void NGSimpleKeypad::processingLoop() {
    for (int i = 0; i < _keyCount; i++) {
        if ((millis() - _keys[i].last) >  _keys[i].delay) {
            if (digitalRead(_keys[i].pin) == LOW) {
                if (_callback != nullptr) {
                    _callback(_keys[i].id);
                }
                _keys[i].last = millis();
            }
        }
    }
}
