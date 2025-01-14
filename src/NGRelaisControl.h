//
//  NGRelaisControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.12.21.
//

#ifndef NGRelaisControl_h
#define NGRelaisControl_h

#include <Arduino.h>

class NGRelaisControl {

private:
    byte _pinRelais;
    bool _on = false;

protected:
    void _create(byte pinRelais);

public:
    NGRelaisControl(byte pinRelais);
    
    void initialize();
    
    void on();
    
    void off();
    
    bool isOn();
};

#endif /* NGRelaisControl_h */
