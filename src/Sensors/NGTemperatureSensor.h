//
//  NGTemperatureSensor.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.12.21.
//

#ifndef NGTemperatureSensor_h
#define NGTemperatureSensor_h

#include <Arduino.h>
#include <DHT.h>

// DHT11
// Left   = Signal
// Middle = 5V
// Right  = GND

#define DEFTEMPSENSORTYPE DHT11

class NGTemperatureSensor {

private:
    DHT *_dht;
    char _temperatureAsText[100];
    char _humidityAsText[100];

protected:
    void _create(int pinSensor, int sensorType);

public:
    NGTemperatureSensor(int pinSensor);

    NGTemperatureSensor(int pinSensor, int sensorType);
    
    void initialize();
    
    float getTemperature();
    
    char* getTemperatureAsChar();
    
    float getHumidity();
    
    char* getHumidityAsChar();
};

#endif /* NGTemperatureSensor_h */
