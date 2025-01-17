//
//  NGHallSensor.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 14.01.25.
//

#include <NGHallSensor.h>

NGHallSensor::NGHallSensor() {
    _create(DEFPINHALLSENSOR);
}

NGHallSensor::NGHallSensor(byte pinSensor) {
    _create(pinSensor);
}

void NGHallSensor::_create(byte pinSensor) {
    _pinSensor = pinSensor;
}

void NGHallSensor::initialize() {
    pinMode(_pinSensor, INPUT);
}

bool NGHallSensor::isMagneticFieldDetected() {
    return digitalRead(_pinSensor) == LOW;
}