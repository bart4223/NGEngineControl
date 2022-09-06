//
//  NGSoilMoistureSensor.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.03.22.
//

#include "NGSoilMoistureSensor.h"

NGSoilMoistureSensor::NGSoilMoistureSensor(int pinSensor) {
    _create(pinSensor);
}

void NGSoilMoistureSensor::_create(int pinSensor) {
    _pinSensor = pinSensor;
}

void NGSoilMoistureSensor::initialize() {
    
}

int NGSoilMoistureSensor::getHumidity() {
    return analogRead(_pinSensor);
}
