//
//  NGSimpleDigitalSensor.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 04.03.25.
//

#ifndef NGSimpleDigitalSensor_h
#define NGSimpleDigitalSensor_h

#include <Arduino.h>

class NGSimpleDigitalSensor {

private:
    byte _pinSensor;

protected:
    void _create(byte pinSensor);

public:
    NGSimpleDigitalSensor(byte pinSensor);
    
    void initialize();

    bool isOn();
};

#endif /* NGSimpleDigitalSensor_h */