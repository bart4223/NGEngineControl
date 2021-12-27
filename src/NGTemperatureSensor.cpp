//
//  NGTemperatureSensor.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.12.21.
//

#include "NGStrings.h"
#include "NGTemperatureSensor.h"

NGTemperatureSensor::NGTemperatureSensor(int pinSensor) {
    _create(pinSensor);
}

NGTemperatureSensor::_create(int pinSensor) {
    _dht = new DHT(pinSensor, DHT11);
}

void NGTemperatureSensor::initialize() {
    _dht->begin();
}

float NGTemperatureSensor::getTemperature() {
    return _dht->readTemperature();
}

char* NGTemperatureSensor::getTemperatureAsChar() {
    return FloatToChar(getTemperature());
}

float NGTemperatureSensor::getHumidity() {
    return _dht->readHumidity();
}

char* NGTemperatureSensor::getHumidityAsChar() {
    return FloatToChar(getHumidity());
}
