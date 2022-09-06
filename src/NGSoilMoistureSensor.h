//
//  NGSoilMoistureSensor.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.03.22.
//

#ifndef NGSoilMoistureSensor_h
#define NGSoilMoistureSensor_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class NGSoilMoistureSensor {
    
private:
    int _pinSensor;
    
protected:
    void _create(int pinSensor);
    
public:
    NGSoilMoistureSensor(int pinSensor);

    void initialize();
    
    int getHumidity();
};

#endif /* NGSoilMoistureSensor_h */
