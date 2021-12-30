//
//  NGRealTimeClock.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 30.12.21.
//

#ifndef NGRealTimeClock_h
#define NGRealTimeClock_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "RTClib.h"

// DS3231 -> I2C 0x68

class NGRealTimeClock {

private:
    RTC_DS3231 *_rtc;
    char _nowAsText[100];
    
protected:
    _create();

public:
    NGRealTimeClock();
    
    void initialize();
    
    void initialize(bool adjust);
    
    DateTime getNow();
    
    char* getNowAsText();
};

#endif /* NGRealTimeClock_h */
