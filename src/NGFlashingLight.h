//
//  NGFlashingLight.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 28.09.21.
//

#ifndef NGFlashingLight_h
#define NGFlashingLight_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGITestableComponent.h";

#define DEFFLASHINGINTERVAL 1000

class NGFlashingLight : public NGITestableComponent {
    
private:
    byte _pinFlashingLight;
    int _interval;
    unsigned long _millis;
    bool _flashing;
    bool _on = false;
    
protected:
    void _create(byte pinFlashingLight, int interval);
    
    void _switchFlashingLight(bool on);
    
public:
    NGFlashingLight(byte pinFlashingLight);
    
    NGFlashingLight(byte pinFlashingLight, int interval);
    
    void initialize();
    
    void setOn(bool on);
    
    bool IsOn();
    
    bool ToogleOn();
    
    void processingLoop();
    
    void testSequenceStart();

    void testSequenceStop();
};

#endif /* NGFlashingLight_h */
