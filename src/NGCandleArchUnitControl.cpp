//
//  NGCandleArchUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 20.10.23.
//

#include "Wire.h"
#include "NGCommon.h"
#include "NGExceptionDefinitions.h"
#include "NGMemoryObserver.h"
#include "NGCandleArchUnitControl.h"

NGCandleArchUnitControl::NGCandleArchUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE);
}

NGCandleArchUnitControl::NGCandleArchUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE);
}

NGCandleArchUnitControl::NGCandleArchUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE);
}

NGCandleArchUnitControl::NGCandleArchUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate);
}

void NGCandleArchUnitControl::_create(char* name, byte address, int serialRate) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    Wire.begin(_address);
}

void NGCandleArchUnitControl::_processingReceivedData() {
    
}

void NGCandleArchUnitControl::_processingStartupLoop() {

}

void NGCandleArchUnitControl::_processingIRRemoteData() {
    
}

byte NGCandleArchUnitControl::registerLightingArea(byte switcherLatchPin, byte switcherClockPin, byte switcherDataPin) {
    byte res = _lightingAreaCount;
    if (_lightingAreaCount < MAXLIGHTINGAREACOUNT) {
        candleArchLightingArea cala;
        cala.switcher = new NG8BitShiftRegister(switcherLatchPin, switcherClockPin, switcherDataPin);
        _lightingAreas[_lightingAreaCount] = cala;
        _lightingAreaCount++;
    } else {
        _raiseException(ExceptionTooMuchLightingAreaCount);
    }
    if (_logging) {
        char log[100];
        sprintf(log, "Lighting area %d registered", res);
        writeInfo(log);
    }
    return res;
}

void NGCandleArchUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    for (int i = 0; i < _lightingAreaCount; i++) {
        _lightingAreas[i].switcher->initialize();
        _lightingAreas[i].switcher->setValue(0);
    }
}

void NGCandleArchUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
}

void NGCandleArchUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}

void NGCandleArchUnitControl::testSequenceStart() {
    for (int i = 0; i < _lightingAreaCount; i++) {
        _lightingAreas[i].switcher->initialize();
        _lightingAreas[i].switcher->setValue(255);
    }
}

void NGCandleArchUnitControl::testSequenceStop() {
    for (int i = 0; i < _lightingAreaCount; i++) {
        _lightingAreas[i].switcher->initialize();
        _lightingAreas[i].switcher->setValue(0);
    }
}
