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

void NGCustomUnitControl::_create(char* name, byte address, int serialRate) {
    _name = name;
    _address = address;
    _serialRate = serialRate;
    _initialized = false;
    _logging = true;
}

void NGCustomUnitControl::_processingReceivedData() {
    clearInfo();
    char* cmd = (char*)malloc(_receivedDataCount + 1);
    memcpy(cmd, _receivedData, _receivedDataCount);
    cmd[_receivedDataCount] = '\0';
    writeInfo(cmd);
    free(cmd);
}

void NGCustomUnitControl::initialize() {
    
}

void NGCustomUnitControl::registerNotification(NGCustomNotification *notification) {
    char log[100];
    _notification[_notificationCount] = notification;
    _notification[_notificationCount]->initialize();
    _notificationCount++;
    sprintf(log, "%s registered", _notification[_notificationCount - 1]->getName());
    writeInfo(log);
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

void NGCustomUnitControl::processingLoop() {
    if (_receivedDataCount > 0) {
        _processingReceivedData();
        _receivedDataCount = 0;
    }
}

void NGCustomUnitControl::clearInfo() {
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->clear();
    }
}

void NGCustomUnitControl::writeInfo(char* info) {
    writeInfo(info, 0);
}

void NGCustomUnitControl::writeInfo(char* info, int line) {
    writeInfo(info, line, 0);
}

void NGCustomUnitControl::writeInfo(char* info, int line, int column) {
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->writeInfo(info, line, column);
    }
}
