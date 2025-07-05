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

char* NGOneWireTemperatureSensor::getTemperatureAsChar() {
    _sensor->requestTemperatures();
    float temperature = _sensor->getTempCByIndex(0);
    unsigned char *temp = FloatToChar(temperature);
    memcpy(_temperatureAsText, temp, strlen(temp));
    free(temp);
    return _temperatureAsText;
}