//
//  NGPumpControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.03.22.
//

#include "NGPumpControl.h"

NGPumpControl::NGPumpControl(byte pinPump) {
    _create(pinPump);
}

void NGPumpControl::_create(byte pinPump) {
    _relais = new NGRelaisControl(pinPump);
}

void NGPumpControl::initialize() {
    _relais->initialize();
    off();
}

void NGPumpControl::off() {
    _relais->off();
}

void NGPumpControl::on() {
    _relais->on();
}

bool NGPumpControl::isOn() {
    return _relais->isOn();
}
