//
//  NGDuoLED.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.12.21.
//

#ifndef NGDuoLED_h
#define NGDuoLED_h

#include <Arduino.h>

class NGDuoLED {

private:
    byte _pinLEDOne;
    byte _pinLEDTwo;
    bool _isOneOn = false;
    bool _isTwoOn = false;

protected:
    void _create(byte pinLEDOne, byte pinLEDTwo);

public:
    NGDuoLED(byte pinLEDOne, byte pinLEDTwo);
    
    void initialize();
    
    void turnOneOff();
    
    void turnTwoOff();
    
    void turnOff();
    
    void turnOneOn();
    
    void turnTwoOn();
    
    void turnOn();
    
    bool isOneOn();
    
    bool isTwoOn();
    
    bool isOn();
    
    void toggle();
};

#endif /* NGDuoLED_h */
