//
//  NGHallSensor.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 14.01.25.
//

#ifndef NGHallSensor_h
#define NGHallSensor_h

#include <Arduino.h>

#define DEFPINHALLSENSOR 2

class NGHallSensor {

private:
    byte _pinSensor;

protected:
    void _create(byte pinSensor);

public:
    NGHallSensor();
    
    NGHallSensor(byte pinSensor);
    
    void initialize();

    bool isMagneticFieldDetected();
};

#endif /* NGHallSensor_h */