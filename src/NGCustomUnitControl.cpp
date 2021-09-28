//
//  NGCustomUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.06.21.
//

#include "NGCommon.h"
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

void NGCustomUnitControl::initialize() {
    if (_pinStartup != -1) {
        pinMode(_pinStartup, INPUT_PULLUP);
    }
}

void NGCustomUnitControl::processingLoop() {
    if (_pinStartup != -1 && !_started) {
        while(digitalRead(_pinStartup));
    }
    _started = true;
}

void NGCustomUnitControl::setWorkMode(workMode workmode) {
    if (_workMode = workmode) {
        _workMode = workmode;
        _writeState();
    }
}

workMode NGCustomUnitControl::getWorkMode() {
    return _workMode;
}

void NGCustomUnitControl::setStartup(int pinStartup) {
    _pinStartup = pinStartup;
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

void NGCustomUnitControl::_clearState() {
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->clear(1);
    }
}

void NGCustomUnitControl::_writeState() {
    char state[100];
    _clearState();
    sprintf(state, "%s %s wM%d", _name, _version, _workMode);
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->writeInfo(state, 1, 0);
    }
}

void NGCustomUnitControl::_raiseException(int id) {
    char info[100];
    clearInfo();
    _exceptionCount++;
    sprintf(info, "Ex %d(%d)", id, _exceptionCount);
    writeInfo(info);
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
