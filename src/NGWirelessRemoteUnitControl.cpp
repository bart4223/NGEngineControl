//
//  NGWirelessRemoteUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 13.08.22.
//

#include "Wire.h"
#include "NGCommon.h"
#include "NGMemoryObserver.h"
#include "NGWirelessRemoteUnitControl.h"

NGWirelessRemoteUnitControl::NGWirelessRemoteUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE);
}

NGWirelessRemoteUnitControl::NGWirelessRemoteUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE);
}

NGWirelessRemoteUnitControl::NGWirelessRemoteUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE);
}

NGWirelessRemoteUnitControl::NGWirelessRemoteUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate);
}

void NGWirelessRemoteUnitControl::_create(char* name, byte address, int serialRate) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    Wire.begin(_address);
}

void NGWirelessRemoteUnitControl::_processingReceivedData() {
    
}

void NGWirelessRemoteUnitControl::_processingStartupLoop() {

}

void NGWirelessRemoteUnitControl::_processingIRRemoteData() {
    
}

byte NGWirelessRemoteUnitControl::registerJoystick() {
    return registerJoystick((char*)"");
}

byte NGWirelessRemoteUnitControl::registerJoystick(char* name) {
    return registerJoystick(name, DEFJOYSTICKPINX, DEFJOYSTICKPINY, DEFJOYSTICKPINFIRE);
}

byte NGWirelessRemoteUnitControl::registerJoystick(char* name, byte joystickPinX, byte joystickPinY, byte joystickPinFire) {
    byte res = _remoteControlCount;
    if (_remoteControlCount < MAXWIRELESSREMOTECONTROLCOUNT) {
        wirelessRemoteControl wrc;
        wrc.kind = wrckJoystick;
        wrc.joystick = new NGJoystickControl(_remoteControlCount, joystickPinX, joystickPinY, joystickPinFire);
        wrc.name = name;
        _remoteControls[_remoteControlCount] = wrc;
        _remoteControlCount++;
    } else {
        _raiseException(ExceptionTooMuchWirelessRemoteControlCount);
    }
    if (_logging) {
        char log[100];
        if (_name != "") {
            sprintf(log, "Joystick \"%s\" registered", name);
        } else {
            sprintf(log, "Joystick %d registered", res);
        }
        writeInfo(log);
    }
    return res;
}

void NGWirelessRemoteUnitControl::addJoystickAction(byte joystick, int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, int delay, joystickMovement movement) {
    _remoteControls[joystick].joystick->registerAction(pin, mode, axis, kind, threshold, delay, movement);
}

void NGWirelessRemoteUnitControl::setLastInfoDelay(int lastinfodelay) {
    _lastInfoDelay = lastinfodelay;
}

void NGWirelessRemoteUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    for (int i = 0; i < _remoteControlCount; i++) {
        switch(_remoteControls[i].kind) {
            case wrckJoystick:
                _remoteControls[i].joystick->initialize();
                break;
        }
    }
}

void NGWirelessRemoteUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    for (int i = 0; i < _remoteControlCount; i++) {
        switch(_remoteControls[i].kind) {
            case wrckJoystick:
                _remoteControls[i].joystick->processingLoop();
                if (_remoteControls[i].joystick->hasLastMovement()) {
                    char log[100];
                    sprintf(log, "%s fired", _remoteControls[i].name);
                    joystickMovement lastMovement = _remoteControls[i].joystick->getLastMovement();
                    int infoID = i * 10 + (int)lastMovement;
                    switch(lastMovement) {
                        case jmUp:
                            sprintf(log, "%s up", log);
                            break;
                        case jmDown:
                            sprintf(log, "%s down", log);
                            break;
                        case jmLeft:
                            sprintf(log, "%s left", log);
                            break;
                        case jmRight:
                            sprintf(log, "%s right", log);
                            break;
                        case jmFire:
                            sprintf(log, "%s button", log);
                            break;
                    }
                    if (infoID != _lastInfoID) {
                        clearInfo();
                        writeInfo(log);
                        _lastInfoID = infoID;
                    }
                    if (_logging) {
                        Serial.println(_lastInfoID);
                        Serial.println(log);
                    }
                    _lastInfo = millis();
                }
                break;
        }
    }
    if ((_lastInfo != -1) && (millis() - _lastInfo) > _lastInfoDelay) {
        _lastInfo = -1;
        _lastInfoID = -1;
        clearInfo();
    }
    switch (_workMode) {
        case wmNone:
            break;
        case wmObserveMemory:
            observeMemory(OBSERVEMEMORYDELAY);
            break;
        case wmSpec:
            observeMemory(OBSERVEMEMORYDELAY);
            break;
    }
}

void NGWirelessRemoteUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}
