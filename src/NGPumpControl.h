//
//  NGPumpControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.03.22.
//

#ifndef NGPumpControl_h
#define NGPumpControl_h

#include <Arduino.h>
#include <NGRelaisControl.h>

class NGPumpControl {

private:
    NGRelaisControl *_relais;

protected:
    void _create(byte pinPump);

public:
    NGPumpControl(byte pinPump);
    
    void initialize();
    
    void on();
    
    void off();
    
    bool isOn();
};

#endif /* NGPumpControl_hpp */
