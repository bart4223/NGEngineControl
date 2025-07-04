//
//  NGTemperatureSensor.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.12.21.
//

#include "Common/NGStrings.h"
#include "NGTemperatureSensor.h"

NGTemperatureSensor::NGTemperatureSensor(int pinSensor) {
    _create(pinSensor, DEFTEMPSENSORTYPE);
}

NGTemperatureSensor::NGTemperatureSensor(int pinSensor, int sensorType) {
    _create(pinSensor, sensorType);
}

void NGTemperatureSensor::_create(int pinSensor, int sensorType) {
    _dht = new DHT(pinSensor, sensorType);
}

void NGTemperatureSensor::initialize() {
    _dht->begin();
}

float NGTemperatureSensor::getTemperature() {
    return _dht->readTemperature();
}

char* NGTemperatureSensor::getTemperatureAsChar() {
    unsigned char *temp = FloatToChar(getTemperature());
    memcpy(_temperatureAsText, temp, strlen(temp));
    free(temp);
    return _temperatureAsText;
}

float NGTemperatureSensor::getHumidity() {
    return _dht->readHumidity();
}

char* NGTemperatureSensor::getHumidityAsChar() {
    unsigned char *humi = FloatToChar(getHumidity());
    memcpy(_humidityAsText, humi, strlen(humi));
    free(humi);    
    return _humidityAsText;
}
