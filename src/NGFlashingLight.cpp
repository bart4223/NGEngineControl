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

void NGFlashingLight::_create(byte pinFlashingLight, int interval) {
    _pinFlashingLight = pinFlashingLight;
    _interval = interval;
    _flashing = false;
}

void NGFlashingLight::_switchFlashingLight(bool on) {
    if (on) {
        digitalWrite(_pinFlashingLight, HIGH);
    } else {
        digitalWrite(_pinFlashingLight, LOW);
    }
}

void NGFlashingLight::initialize() {
    pinMode(_pinFlashingLight, OUTPUT);
    _switchFlashingLight(false);
}

void NGFlashingLight::processingLoop() {
    unsigned long m = millis();
    if (_on && (m - _millis >= _interval)) {
        _flashing = !_flashing;
        _switchFlashingLight(_flashing);
        _millis = m;
    }
}

void NGFlashingLight::setOn(bool on) {
    _on = on;
    if (!_on) {
        _switchFlashingLight(_on);
    }
}

bool NGFlashingLight::IsOn() {
    return _on;
}

bool NGFlashingLight::ToogleOn() {
    setOn(!IsOn());
}

void NGFlashingLight::testSequenceStart() {
    _switchFlashingLight(true);
}

void NGFlashingLight::testSequenceStop() {
    _switchFlashingLight(false);
}
