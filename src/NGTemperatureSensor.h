//
//  NGTemperatureSensor.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.12.21.
//

#ifndef NGTemperatureSensor_h
#define NGTemperatureSensor_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "DHT.h"

// DHT11
// Left   = Signal
// Middle = 5V
// Right  = GND

class NGTemperatureSensor {

private:
    DHT *_dht;

protected:
    _create(int pinSensor);

public:
    NGTemperatureSensor(int pinSensor);
    
    void initialize();
    
    float getTemperature();
    
    char* getTemperatureAsChar();
    
    float getHumidity();
    
    char* getHumidityAsChar();
};

#endif /* NGTemperatureSensor_h */
