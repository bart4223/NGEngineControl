//
//  NGCustomUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.06.21.
//

#include "NGCommon.h"
#include "NGMemoryObserver.h"
#include "NGCustomUnitControl.h"

void setGlobalUnit(NGCustomUnitControl *unit) {
    _globalUnit = unit;
}

bool hasGlobalUnit() {
    return _globalUnit != NULL;
}

void globalUnitReceiveDataStart() {
    if (hasGlobalUnit) {
        _globalUnit->receiveDataStart();
    }
}

void globalUnitReceivedData(int index, byte data) {
    if (hasGlobalUnit) {
        _globalUnit->receivedData(index, data);
    }
}

void globalUnitReceiveDataFinish(int count) {
    if (hasGlobalUnit) {
        _globalUnit->receiveDataFinish(count);
    }
}

void globalUnitRequestData(byte* data) {
    if (hasGlobalUnit) {
        return _globalUnit->requestData(data);
    }
}

void NGCustomUnitControl::_create(char* name, byte address, int serialRate) {
    _name = name;
    _address = address;
    _serialRate = serialRate;
    _initialized = false;
    _logging = true;
}

void NGCustomUnitControl::_clearState() {
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->clear(1);
    }
}

void NGCustomUnitControl::_writeState() {
    char state[100];
    _clearState();
    #ifdef NG_PLATFORM_MEGA
    if (_rtc != nullptr) {
        sprintf(state, "%s %s wM%d (C) by NG 2021-%s", _name, _version, _workMode, _rtc->getShortYearAsText());
    } else {
        sprintf(state, "%s %s wM%d (C) by NG MMXXII", _name, _version, _workMode);
    }
    #else
    sprintf(state, "%s %s wM%d", _name, _version, _workMode);
    #endif
    if (_rtc != nullptr) {
        sprintf(state, "%s %s", state, _rtc->getDateAsText());
    }
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->writeInfo(state, 1, 0);
    }
}

void NGCustomUnitControl::_writeTime() {
    if (_rtc != nullptr) {
        writeInfo(_rtc->getTimeAsText());
    }
}

void NGCustomUnitControl::_raiseException(int id) {
    char info[100];
    clearInfo();
    _exceptionCount++;
    sprintf(info, "Ex %d(%d)", id, _exceptionCount);
    writeInfo(info);
}

void NGCustomUnitControl::initialize() {
    if (_pinStartup != -1) {
        pinMode(_pinStartup, INPUT_PULLUP);
    }
}

long int NGCustomUnitControl::startUp() {
    _writeState();
    observeMemory(0);
    if (_pinStartup != -1) {
        while(digitalRead(_pinStartup)) {
            _processingStartupLoop();
        }
    }
    return millis();
}

void NGCustomUnitControl::processingLoop() {
    
}

void NGCustomUnitControl::setWorkMode(workMode workmode) {
    if (_workMode != workmode) {
        _workMode = workmode;
        _writeState();
    }
}

workMode NGCustomUnitControl::getWorkMode() {
    return _workMode;
}

void NGCustomUnitControl::registerStartup(int pinStartup) {
    _pinStartup = pinStartup;
}

void NGCustomUnitControl::registerRealTimeClock(NGRealTimeClock *rtc) {
    _rtc = rtc;
    #ifdef NG_PLATFORM_MEGA
    writeInfo("RTC registered");
    #endif
}

void NGCustomUnitControl::registerNotification(NGCustomNotification *notification) {
    if (_notificationCount < NOTIFICATIONCOUNT) {
        char log[100];
        _notification[_notificationCount] = notification;
        _notification[_notificationCount]->initialize();
        _notificationCount++;
        sprintf(log, "%s registered", _notification[_notificationCount - 1]->getName());
        writeInfo(log);
    } else {
        _raiseException(ExceptionTooMuchNotificationCount);
    }    
}

void NGCustomUnitControl::receiveDataStart() {
    _receivingData = true;
    _receivedDataCount = 0;
}

void NGCustomUnitControl::receivedData(int index, byte data) {
    _receivedData[index] = data;
}

void NGCustomUnitControl::receiveDataFinish(int count) {
    _receivingData = false;
    _receivedDataCount = count;
}

void NGCustomUnitControl::clearInfo() {
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->clear(0);
    }
}

void NGCustomUnitControl::writeInfo(char* info) {
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->writeInfo(info, 0, 0);
    }
}
