//
//  NGOneWireTemperatureSensor.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 05.07.25.
//

#ifndef NGOneWireTemperatureSensor_h
#define NGOneWireTemperatureSensor_h

#include <Arduino.h>
#include <DallasTemperature.h>

#define DEFPINTEMPERATURESENSOR 2

class NGOneWireTemperatureSensor {

private:
    DallasTemperature *_sensor;
    char _temperatureAsText[100];

protected:
    void _create(byte pinSensor);

public:
    NGOneWireTemperatureSensor();
    
    NGOneWireTemperatureSensor(byte pinSensor);
    
    void initialize();

    float getTemperatureAsFloat();
    
    char* getTemperatureAsChar();
};

#endif /* NGOneWireTemperatureSensor_h */