//
//  NGContactObjectRecognizer.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.10.21.
//

#include "NGContactObjectRecognizer.h"

NGContactObjectRecognizer::NGContactObjectRecognizer() {
    _create(cpmInputPullup, DEF_INPUT_PIN);
}

NGContactObjectRecognizer::NGContactObjectRecognizer(byte pin) {
    _create(cpmInputPullup, pin);
}

NGContactObjectRecognizer::NGContactObjectRecognizer(contactPinMode pinMode, byte pin) {
    _create(pinMode, pin);
}

void NGContactObjectRecognizer::_create(contactPinMode pinMode, byte pin) {
    _pinMode = pinMode;
    _pin = pin;
}

void NGContactObjectRecognizer::initialize() {
    switch(_pinMode) {
        case cpmInput:
            pinMode(_pin, INPUT);
            break;
        case cpmInputPullup:
            pinMode(_pin, INPUT_PULLUP);
            break;
    }
}

bool NGContactObjectRecognizer::detected() {
    bool res = false;
    switch(_pinMode) {
        case cpmInput:
            if (digitalRead(_pin)) {
                if (!_detected) {
                    res = true;
                    _detected = res;
                }
            } else {
                _detected = false;
            }
            break;
        case cpmInputPullup:
            if (!digitalRead(_pin)) {
                if (!_detected) {
                    res = true;
                    _detected = res;
                }
            } else {
                _detected = false;
            }
            break;
    }
    return res;
}

bool NGContactObjectRecognizer::hasDetected() {
    return _detected;
}

int NGContactObjectRecognizer::getCloseness() {
    return 0;
}
