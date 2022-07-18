//
//  NGCurrentSensor.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 16.07.22.
//

#ifndef NGCurrentSensor_h
#define NGCurrentSensor_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define DEFPINLIGHTSENSOR A0
#define DEFCURRENTSENSORTECHNOLOGY cst5Ampere

enum CurrentSensorTechnology{ cst5Ampere, cst20Ampere, cst30Ampere };

class NGCurrentSensor {

private:
    byte _pinSensor;
    CurrentSensorTechnology _sensorTechnology;
    int _mVpA;
    
protected:
    _create(CurrentSensorTechnology sensorTechnology, byte pinSensor);
    
public:
    NGCurrentSensor();
    
    NGCurrentSensor(byte pinSensor);
    
    NGCurrentSensor(CurrentSensorTechnology sensorTechnology);
    
    NGCurrentSensor(CurrentSensorTechnology sensorTechnology, byte pinSensor);
    
    void initialize();
    
    int getCurrent();
    
    int getCurrentAbs();
};
    
#endif /* NGCurrentSensor_h */
