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

#define DEFFLASHINGINTERVAL 1000

class NGFlashingLight {
    
private:
    byte _pinFlashingLight;
    int _interval;
    unsigned long _millis;
    bool _flashing;
    bool _on = false;
    
protected:
    _create(byte pinFlashingLight, int interval);
    
public:
    NGFlashingLight(byte pinFlashingLight);
    
    NGFlashingLight(byte pinFlashingLight, int interval);
    
    void initialize();
    
    void setOn(bool on);
    
    bool IsOn();
    
    bool ToogleOn();
    
    void processingLoop();
};

#endif /* NGFlashingLight_h */
