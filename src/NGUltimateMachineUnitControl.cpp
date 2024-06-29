//
//  NGUltimateMachineUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 23.06.24.
//

#include "Wire.h"
#include "NGCommon.h"
#include "NGUltimateMachineUnitControl.h"

NGUltimateMachineUnitControl::NGUltimateMachineUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE, DEFAULTPINPOWERSWITCH, DEFAULTPINFINGER, DEFAULTZEROPOSITIONFINGER, DEFAULTMINPOSITIONFINGER, DEFAULTMAXPOSITIONFINGER, DEFAULTSTEPWIDTHFINGER);
}

NGUltimateMachineUnitControl::NGUltimateMachineUnitControl(char* name, byte pinPowerSwitch, byte pinFinger, byte zeroPositionFinger, byte minPositionFinger, byte maxPositionFinger, byte stepWidthFinger) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE, pinPowerSwitch, pinFinger, zeroPositionFinger, minPositionFinger, maxPositionFinger, stepWidthFinger);
}

NGUltimateMachineUnitControl::NGUltimateMachineUnitControl(char* name, byte address, byte pinPowerSwitch, byte pinFinger, byte zeroPositionFinger, byte minPositionFinger, byte maxPositionFinger, byte stepWidthFinger) {
    _create(name, address, DEFAULTSERIALRATE, pinPowerSwitch, pinFinger, zeroPositionFinger, minPositionFinger, maxPositionFinger, stepWidthFinger);
}

NGUltimateMachineUnitControl::NGUltimateMachineUnitControl(char* name, byte address, int serialRate, byte pinPowerSwitch, byte pinFinger, byte zeroPositionFinger, byte minPositionFinger, byte maxPositionFinger, byte stepWidthFinger) {
    _create(name, address, serialRate, pinPowerSwitch, pinFinger, zeroPositionFinger, minPositionFinger, maxPositionFinger, stepWidthFinger);
}

void NGUltimateMachineUnitControl::_create(char* name, byte address, int serialRate, byte pinPowerSwitch, byte pinFinger, byte zeroPositionFinger, byte minPositionFinger, byte maxPositionFinger, byte stepWidthFinger) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    Wire.begin(_address);
    _powerSwitch = new NGRelaisControl(pinPowerSwitch);
    _finger = new NGServoControl(pinFinger, zeroPositionFinger, minPositionFinger, maxPositionFinger, stepWidthFinger);
}

void NGUltimateMachineUnitControl::_processingReceivedData() {
    
}

void NGUltimateMachineUnitControl::_processingStartupLoop() {

}

void NGUltimateMachineUnitControl::_processingIRRemoteData() {
    
}

void NGUltimateMachineUnitControl::setProcessDelay(int delay) {
    _processDelay = delay;
}

void NGUltimateMachineUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    _powerSwitch->initialize();
    _powerSwitch->on();
    if (_logging) {
        writeInfo("Power switch is on");
    }
    _finger->initialize();
    _finger->setLogging(_logging);
    if (_logging) {
        writeInfo("Finger is initialized");
    }
    _lastProcessStep = millis();
}

void NGUltimateMachineUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    if (millis() - _lastProcessStep > _processDelay) {
        switch(_processStep) {
            case 0:
                if (!_finger->isMaxPosition()) {
                    _finger->stepUp();
                } else {
                    _processStep++;
                }
                break;
            case 1:
                if (!_finger->isMinPosition()) {
                    _finger->stepDown();
                } else {
                    _processStep++;
                }
                break;
            case 2:
                _powerSwitch->off();
                if (_logging) {
                    writeInfo("Power switch is off");
                }
                _processStep++;
                break;
        }
        _lastProcessStep = millis();
    }
}

void NGUltimateMachineUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}
