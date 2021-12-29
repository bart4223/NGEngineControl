//
//  NGRelaisControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.12.21.
//

#include "NGRelaisControl.h"

NGRelaisControl::NGRelaisControl(byte pinRelais) {
    _create(pinRelais);
}

NGRelaisControl::_create(byte pinRelais) {
    _pinRelais = pinRelais;
}

void NGRelaisControl::initialize() {
    pinMode(_pinRelais, OUTPUT);
    off();
}

void NGRelaisControl::off() {
    digitalWrite(_pinRelais, LOW);
    _on = false;
}

void NGRelaisControl::on() {
    digitalWrite(_pinRelais, HIGH);
    _on = true;
}

bool NGRelaisControl::isOn() {
    return _on;
}
