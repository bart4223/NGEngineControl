//
//  NGFlashingLight.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 28.09.21.
//

#include "NGFlashingLight.h"

NGFlashingLight::NGFlashingLight(byte pinFlashingLight) {
    _create(pinFlashingLight, DEFFLASHINGINTERVAL);
}

NGFlashingLight::NGFlashingLight(byte pinFlashingLight, int interval) {
    _create(pinFlashingLight, interval);
}

NGFlashingLight::_create(byte pinFlashingLight, int interval) {
    _pinFlashingLight = pinFlashingLight;
    _interval = interval;
    _flashing = false;
}

void NGFlashingLight::initialize() {
    pinMode(_pinFlashingLight, OUTPUT);
    digitalWrite(_pinFlashingLight, LOW);
}

void NGFlashingLight::processingLoop() {
    unsigned long m = millis();
    if (_on && (m - _millis >= _interval)) {
        _flashing = !_flashing;
        if (_flashing) {
            digitalWrite(_pinFlashingLight, HIGH);
        } else {
            digitalWrite(_pinFlashingLight, LOW);
        }
        _millis = m;
    }
}

void NGFlashingLight::setOn(bool on) {
    _on = on;
    if (!_on) {
        digitalWrite(_pinFlashingLight, LOW);
    }
}

bool NGFlashingLight::IsOn() {
    return _on;
}

bool NGFlashingLight::ToogleOn() {
    setOn(!IsOn());
}
