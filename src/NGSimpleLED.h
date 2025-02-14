//
//  NGSimpleLED.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 14.02.25.
//

#ifndef NGSimpleLED_h
#define NGSimpleLED_h

#include <Arduino.h>

#define DEFPINLED 6

class NGSimpleLED {

private:
    byte _pinLED;
    bool _on = false;

protected:
    void _create(byte pinLED);

    void _switch(bool on);

public:
    NGSimpleLED();
    
    NGSimpleLED(byte pinLED);
    
    void initialize();

    void on();

    void off();

    bool isOn();
};

#endif /* NGSimpleLED_h */