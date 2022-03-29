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

NGPumpControl::_create(byte pinPump) {
    _pump = new NGRelaisControl(pinPump);
}

void NGPumpControl::initialize() {
    _pump->initialize();
    off();
}

void NGPumpControl::off() {
    _pump->off();
}

void NGPumpControl::on() {
    _pump->on();
}

bool NGPumpControl::isOn() {
    return _pump->isOn();
}
