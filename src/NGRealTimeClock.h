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
    String _nowAsString;
    bool _use32K = false;
    
protected:
    _create(bool use32K);
    char* _getNowAsText(char* format);

public:
    NGRealTimeClock();
    
    NGRealTimeClock(bool use32K);
    
    void initialize();
    
    void initialize(bool adjust);
    
    DateTime getNow();
    
    char* getNowAsText();

    char* getDateAsText();

    char* getYearAsText();

    char* getShortYearAsText();
    
    char* getTimeAsText();
    
    bool isXMas();
};

#endif /* NGRealTimeClock_h */
