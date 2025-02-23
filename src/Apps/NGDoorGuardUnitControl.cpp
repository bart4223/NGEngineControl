//
//  NGDoorGuardUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 18.02.25.
//

#include "NGExceptionDefinitions.h"
#include <Apps/NGDoorGuardUnitControl.h>

NGDoorGuardUnitControl::NGDoorGuardUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE);
}

NGDoorGuardUnitControl::NGDoorGuardUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE);
}

NGDoorGuardUnitControl::NGDoorGuardUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE);
}

NGDoorGuardUnitControl::NGDoorGuardUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate);
}

void NGDoorGuardUnitControl::_create(char* name, byte address, int serialRate) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    Wire.begin(_address);
}

void NGDoorGuardUnitControl::_processingReceivedData() {
    
}

void NGDoorGuardUnitControl::_processingStartupLoop() {

}

void NGDoorGuardUnitControl::_processingIRRemoteData() {
    
}

void NGDoorGuardUnitControl::_logDoorState(byte door, bool closed) {
    char log[100];
    if (closed) {
        sprintf(log, "Door %d closed", door);
        writeInfo(log);
    } else {
        sprintf(log, "Door %d opened", door);
        writeInfo(log);
    }
}

byte NGDoorGuardUnitControl::registerDoor(NGHallSensor *sensor, NGIEffect *effectopen, NGIEffect *effectclose) {
    byte res = _doorCount;
    if (_doorCount < MAXDOORITEMCOUNT) {
        doorItem di;
        di.sensor = sensor;
        di.effectOpen = effectopen;
        di.effectClose = effectclose;
        di.closed = false;
        _doors[res] = di;
        _doorCount++;
    } else {
        _raiseException(ExceptionTooMuchDoorCount);
    }
    if (_logging) {
        char log[100];
        sprintf(log, "Door %d registered", res);
        writeInfo(log);
    }
    return res;
}

void NGDoorGuardUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    for (int i = 0; i < _doorCount; i++) {
        _doors[i].sensor->initialize();
        _doors[i].closed = _doors[i].sensor->isMagneticFieldDetected();
        if (_logging) {
            _logDoorState(i, _doors[i].closed);
        }
        _doors[i].effectOpen->initialize();
        _doors[i].effectClose->initialize();
    }
}

void NGDoorGuardUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    for (int i = 0; i < _doorCount; i++) {
        bool closed = _doors[i].sensor->isMagneticFieldDetected();
        if (_doors[i].closed) {
            if (!closed) {
                if (_logging) {
                    _logDoorState(i, closed);
                }
            }
        } else {
            if (closed) {
                if (_logging) {
                    _logDoorState(i, closed);
                }
            }
        }
        _doors[i].closed = closed;
        if ( _doors[i].closed) {
            _doors[i].effectClose->processingLoop();
        } else {
            _doors[i].effectOpen->processingLoop();
        }
    }
}

void NGDoorGuardUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}