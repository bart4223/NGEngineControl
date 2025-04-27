//
//  NGRealTimeClock.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 30.12.21.
//

#include "NGStrings.h"
#include "NGRealTimeClock.h"

NGRealTimeClock::NGRealTimeClock() {
    _create(false);
}

NGRealTimeClock::NGRealTimeClock(bool use32K) {
    _create(use32K);
}

void NGRealTimeClock::_create(bool use32K) {
    _rtc = new RTC_DS3231();
    _use32K = use32K;
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
    if (!_use32K) {
        _rtc->disable32K();
    }
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

char* NGRealTimeClock::getYearAsText() {
    char buf[] = "YYYY";
    return _getNowAsText(buf);
}

char* NGRealTimeClock::getShortYearAsText() {
    char buf[] = "YY";
    return _getNowAsText(buf);
}

char* NGRealTimeClock::getTimeAsText() {
    char buf[] = "hh:mm:ss";
    return _getNowAsText(buf);
}

bool NGRealTimeClock::isXMas() {
    DateTime dt = getNow();
    return (dt.month() == 12 && dt.day() > 23 && dt.day() < 27);
}

int NGRealTimeClock::getSecond() {
    DateTime dt = getNow();
    return dt.second();
}

void NGRealTimeClock::resetSeconds() {
    DateTime dt = getNow();
    _rtc->adjust(DateTime(dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), 0));
}

int NGRealTimeClock::getMinute() {
    DateTime dt = getNow();
    return dt.minute();
}

void  NGRealTimeClock::setMinute(int minute) {
    DateTime dt = getNow();
    _rtc->adjust(DateTime(dt.year(), dt.month(), dt.day(), dt.hour(), minute, dt.second()));
}

void NGRealTimeClock::incrementMinute() {
    incrementMinute(true);
}

void NGRealTimeClock::incrementMinute(bool withresetseconds) {
    int minute = getMinute() + 1;
    if (minute > 59) {
        minute = 0;
    }
    setMinute(minute);
    if (withresetseconds) {
        resetSeconds();
    }
}

int NGRealTimeClock::getHour() {
    DateTime dt = getNow();
    return dt.hour();
}

void  NGRealTimeClock::setHour(int hour) {
    DateTime dt = getNow();
    _rtc->adjust(DateTime(dt.year(), dt.month(), dt.day(), hour, dt.minute(), dt.second()));
}

void NGRealTimeClock::incrementHour() {
    int hour = getHour() + 1;
    if (hour > 23) {
        hour = 0;
    }
    setHour(hour);
}