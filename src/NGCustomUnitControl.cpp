//
//  NGCustomUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.06.21.
//

#include "NGCommon.h"
#include "NGCustomUnitControl.h"

void NGCustomUnitControl::_create(char* name, int serialRate) {
    _name = name;
    _serialRate = serialRate;
    _initialized = false;
    _logging = true;
}

void NGCustomUnitControl::_writeInfo(char* info) {
    if (_notification != NULL) {
        _notification->writeInfo(info);
    }
}

void NGCustomUnitControl::initialize() {
    
}

void NGCustomUnitControl::registerNotification(NGCustomNotification *notification) {
    _notification = notification;
    if (_notification != NULL) {
        _notification->initialize();
    }
    char log[100];
    sprintf(log, "%s registered", _notification->getName());
    _writeInfo(log);
}
