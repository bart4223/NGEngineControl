//
//  NGSimpleDigitalSensor.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 04.03.25.
//

#include <Sensors/NGSimpleDigitalSensor.h>

NGSimpleDigitalSensor::NGSimpleDigitalSensor(byte pinSensor) {
    _create(pinSensor);
}

void NGSimpleDigitalSensor::_create(byte pinSensor) {
    _pinSensor = pinSensor;
}

void NGSimpleDigitalSensor::initialize() {
    pinMode(_pinSensor, INPUT_PULLUP);
}

bool NGSimpleDigitalSensor::isOn() {
    return digitalRead(_pinSensor) == LOW;
}