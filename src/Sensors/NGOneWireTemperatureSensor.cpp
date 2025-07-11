//
//  NGOneWireTemperatureSensor.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 05.07.25.
//

#include <OneWire.h>
#include "Common/NGStrings.h"
#include <Sensors/NGOneWireTemperatureSensor.h>

NGOneWireTemperatureSensor::NGOneWireTemperatureSensor() {
    _create(DEFPINTEMPERATURESENSOR);
}

NGOneWireTemperatureSensor::NGOneWireTemperatureSensor(byte pinSensor) {
    _create(pinSensor);
}

void NGOneWireTemperatureSensor::_create(byte pinSensor) {
   _sensor = new DallasTemperature(new OneWire(pinSensor));
}

void NGOneWireTemperatureSensor::initialize() {
     _sensor->begin();
}

float NGOneWireTemperatureSensor::getTemperatureAsFloat() {
    _sensor->requestTemperatures();
    return _sensor->getTempCByIndex(0);
}

char* NGOneWireTemperatureSensor::getTemperatureAsChar() {
    unsigned char *temp = FloatToChar(getTemperatureAsFloat());
    memcpy(_temperatureAsText, temp, strlen(temp));
    free(temp);
    return _temperatureAsText;
}