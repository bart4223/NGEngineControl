//
//  NGRealTimeClock.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 30.12.21.
//

#include "NGStrings.h"
#include "NGRealTimeClock.h"

NGRealTimeClock::NGRealTimeClock() {
    _create();
}

NGRealTimeClock::_create() {
    _rtc = new RTC_DS3231();
}

void NGRealTimeClock::initialize() {
    initialize(false);
}

void NGRealTimeClock::initialize(bool adjust) {
    _rtc->begin();
    if (adjust) {
        _rtc->adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

DateTime NGRealTimeClock::getNow() {
    return _rtc->now();
}

char* NGRealTimeClock::getNowAsText() {
    DateTime now = getNow();
    char *month = LeftPadInteger(now.month(), 2);
    char *day = LeftPadInteger(now.day(), 2);
    char *hour = LeftPadInteger(now.hour(), 2);
    char *minute = LeftPadInteger(now.minute(), 2);
    char *second = LeftPadInteger(now.second(), 2);
    sprintf(_nowAsText, "%s.%s.%d %s:%s:%s", day, month, now.year(), hour, minute, second);
    free(month);
    free(day);
    free(hour);
    free(minute);
    free(second);
    return _nowAsText;
}
