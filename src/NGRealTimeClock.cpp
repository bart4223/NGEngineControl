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

char* NGRealTimeClock::_getNowAsText(char *format) {
    _nowAsString = getNow().toString(format);
    return _nowAsString.c_str();
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
    char buf[] = "DD.MM.YYYY hh:mm:ss";
    return _getNowAsText(buf);
}

char* NGRealTimeClock::getDateAsText() {
    char buf[] = "DD.MM.YYYY";
    return _getNowAsText(buf);
}

char* NGRealTimeClock::getTimeAsText() {
    char buf[] = "hh:mm:ss";
    return _getNowAsText(buf);
}


