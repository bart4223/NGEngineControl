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
    registerKey(pin, id, delay, simpleKeyMode::skmLow);
}

void NGSimpleKeypad::registerKey(byte pin, byte id, int delay, simpleKeyMode mode) {
    simpleKeypadData key;
    key.mode = mode;
    key.pin = pin;
    key.id = id;
    key.delay = delay;
    _keys[_keyCount] = key;
    _keyCount++;
}

void NGSimpleKeypad::initialize() {
    for (int i = 0; i < _keyCount; i++) {
        switch(_keys[i].mode) {
            case skmLow:
                pinMode(_keys[i].pin, INPUT_PULLUP);
                break;
            case skmHigh:
                pinMode(_keys[i].pin, INPUT);
                break;
        }
    }
}

void NGSimpleKeypad::processingLoop() {
    for (int i = 0; i < _keyCount; i++) {
        if ((millis() - _keys[i].last) >  _keys[i].delay) {
            bool fire = false;
            switch(_keys[i].mode) {
                case skmLow:
                    fire = digitalRead(_keys[i].pin) == LOW;
                    break;
                case skmHigh:
                    fire = digitalRead(_keys[i].pin) == HIGH;
                    break;
            }
            if (fire) {
                if (_callback != nullptr) {
                    _callback(_keys[i].id);
                }
                _keys[i].last = millis();
            }
        }
    }
}
