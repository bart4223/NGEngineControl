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
    byte res = _remoteControlCount;
    if (_remoteControlCount < MAXWIRELESSREMOTECONTROLCOUNT) {
        wirelessRemoteControl wrc;
        wrc.kind = wrckJoystick;
        wrc.joystick = new NGJoystickControl();
        _remoteControls[_remoteControlCount] = wrc;
        _remoteControlCount++;
    } else {
        _raiseException(ExceptionTooMuchWirelessRemoteControlCount);
    }
    if (_logging) {
        char log[100];
        sprintf(log, "Joystick %d registered", res);
        writeInfo(log);
    }
    return res;
}

void NGWirelessRemoteUnitControl::addJoystickAction(byte joystick, int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, int delay) {
    _remoteControls[joystick].joystick->registerAction(pin, mode, axis, kind, threshold, delay);
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
                break;
        }
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
