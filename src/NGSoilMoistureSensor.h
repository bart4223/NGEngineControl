//
//  NGSoilMoistureSensor.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.03.22.
//

#ifndef NGSoilMoistureSensor_h
#define NGSoilMoistureSensor_h

#include <Arduino.h>

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
