//
//  NGLaserCannon.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.10.21.
//

#ifndef NGLaserCannon_h
#define NGLaserCannon_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGITestableComponent.h>

class NGLaserCannon : public NGITestableComponent {

private:
    byte _pinLaserCannon;
    bool _fire;

protected:
    _create(byte pinLaserCannon);

public:
    NGLaserCannon(byte pinLaserCannon);
    
    void initialize();
    
    void fireOn();
    
    void fireOff();
    
    bool isFire();
    
    void testSequenceStart();
    
    void testSequenceStop();
};

#endif /* NGLaserCannon_h */
