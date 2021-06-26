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

void NGCustomUnitControl::requestData(byte* data) {
    data[0] = 0x34; //4
    data[1] = 0x32; //2
}

void NGCustomUnitControl::clearInfo() {
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->clear();
    }
}

void NGCustomUnitControl::clearInfo(int line) {
    for (int i = 0; i < _notificationCount; i++ ) {
        _notification[i]->clear(line);
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
