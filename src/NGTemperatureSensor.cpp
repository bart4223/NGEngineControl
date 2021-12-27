//
//  NGTemperatureSensor.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.12.21.
//

#include "NGStrings.h"
#include "NGTemperatureSensor.h"

NGTemperatureSensor::NGTemperatureSensor(int pinSensor) {
    _create(pinSensor, DEFTEMPSENSORTYPE);
}

NGTemperatureSensor::NGTemperatureSensor(int pinSensor, int sensorType) {
    _create(pinSensor, sensorType);
}

NGTemperatureSensor::_create(int pinSensor, int sensorType) {
    _dht = new DHT(pinSensor, sensorType);
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
