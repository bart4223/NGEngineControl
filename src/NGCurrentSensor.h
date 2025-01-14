//
//  NGCurrentSensor.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 16.07.22.
//

#ifndef NGCurrentSensor_h
#define NGCurrentSensor_h

#include <Arduino.h>

#define DEFPINLIGHTSENSOR A0
#define DEFCURRENTSENSORTECHNOLOGY cst5Ampere
#define DEFMINCURRENT 32767

enum CurrentSensorTechnology{ cst5Ampere, cst20Ampere, cst30Ampere };

class NGCurrentSensor {

private:
    byte _pinSensor;
    CurrentSensorTechnology _sensorTechnology;
    int _mVpA;
    int _currentCurrent;
    int _minCurrent = DEFMINCURRENT;
    int _maxCurrent = 0;
    
protected:
    void _create(CurrentSensorTechnology sensorTechnology, byte pinSensor);
    
    void _determineCurrent();
    
public:
    NGCurrentSensor();
    
    NGCurrentSensor(byte pinSensor);
    
    NGCurrentSensor(CurrentSensorTechnology sensorTechnology);
    
    NGCurrentSensor(CurrentSensorTechnology sensorTechnology, byte pinSensor);
    
    void initialize();
    
    int getCurrent();
    
    int getMin();
    
    int getMax();
    
    void reset();
};
    
#endif /* NGCurrentSensor_h */
