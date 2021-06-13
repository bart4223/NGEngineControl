//
//  NGCustomUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.06.21.
//

#include "NGCommon.h"
#include "NGCustomUnitControl.h"

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
