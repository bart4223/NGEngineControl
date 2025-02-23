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

byte NGDoorGuardUnitControl::registerDoor(NGHallSensor *sensor, NGIEffect *effectopenOn, NGIEffect *effectcloseOn) {
    return registerDoor(sensor, dekInfinite, effectopenOn, dekInfinite, effectcloseOn);
}

byte NGDoorGuardUnitControl::registerDoor(NGHallSensor *sensor, doorEffectKind effectKindOpen, NGIEffect *effectopenOn,  doorEffectKind effectKindClose, NGIEffect *effectcloseOn) {
    return registerDoor(sensor, dekInfinite, effectopenOn, nullptr, dekInfinite, effectcloseOn, nullptr);
}

byte NGDoorGuardUnitControl::registerDoor(NGHallSensor *sensor, doorEffectKind effectKindOpen, NGIEffect *effectopenOn,  NGIEffect *effectopenOff, doorEffectKind effectKindClose, NGIEffect *effectcloseOn, NGIEffect *effectcloseOff) {
    byte res = _doorCount;
    if (_doorCount < MAXDOORITEMCOUNT) {
        doorItem di;
        di.sensor = sensor;
        di.effectKindOpen = effectKindOpen;
        di.effectOpenOn = effectopenOn;
        di.effectOpenOff = effectopenOff;
        di.effectKindClose = effectKindClose;
        di.effectCloseOn = effectcloseOn;
        di.effectCloseOff = effectcloseOff;
        di.openDelay = DEFDOOREFFECTDELAY;
        di.closeDelay = DEFDOOREFFECTDELAY;
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

void NGDoorGuardUnitControl::setDoorDelay(byte door, int delayOpen) {
    setDoorDelay(door, delayOpen, DEFDOOREFFECTDELAY);
}

void NGDoorGuardUnitControl::setDoorDelay(byte door, int delayOpen, int delayClose) {
    if (door < _doorCount) {
        _doors[door].openDelay = delayOpen;
        _doors[door].closeDelay = delayClose;
    } else {
        _raiseException(ExceptionInvalidMDoorIndex);
    }
}

void NGDoorGuardUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    for (int i = 0; i < _doorCount; i++) {
        _doors[i].sensor->initialize();
        _doors[i].closed = _doors[i].sensor->isMagneticFieldDetected();
        if (_logging) {
            _logDoorState(i, _doors[i].closed);
        }
        _doors[i].effectOpenOn->initialize();
        _doors[i].effectCloseOn->initialize();
    }
}

void NGDoorGuardUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    for (int i = 0; i < _doorCount; i++) {
        bool closed = _doors[i].sensor->isMagneticFieldDetected();
        if (_doors[i].closed) {
            if (!closed) {
                switch (_doors[i].effectKindOpen) {
                    case dekFinite:
                        _doors[i].lastEffect = millis();
                        break;
                }
                if (_logging) {
                    _logDoorState(i, closed);
                }
            }
        } else {
            if (closed) {
                switch (_doors[i].effectKindClose) {
                    case dekFinite:
                        _doors[i].lastEffect = millis();
                        break;
                }
                if (_logging) {
                    _logDoorState(i, closed);
                }
            }
        }
        _doors[i].closed = closed;
        bool ok = true;
        if (_doors[i].closed) {
            switch (_doors[i].effectKindClose) {
                case dekFinite:
                    ok = (millis() - _doors[i].lastEffect) < _doors[i].closeDelay;
            }
            if (ok) {
                _doors[i].effectCloseOn->processingLoop();
            } else {
                if (_doors[i].effectCloseOff != nullptr) {
                    _doors[i].effectCloseOff->processingLoop();
                }
            } 
        } else {
            switch (_doors[i].effectKindOpen) {
                case dekFinite:
                    ok = (millis() - _doors[i].lastEffect) < _doors[i].openDelay;
            }
            if (ok) {
                _doors[i].effectOpenOn->processingLoop();
            } else {
                if (_doors[i].effectOpenOff != nullptr) {
                    _doors[i].effectOpenOff->processingLoop();
                }
            } 
        }
    }
}

void NGDoorGuardUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}