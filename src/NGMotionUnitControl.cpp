//
//  NGMotionUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 28.09.21.
//

#include "Wire.h"
#include "NGCommon.h"
#include "NGMemoryObserver.h"
#include "NGMotionUnitControl.h"

NGMotionUnitControl::NGMotionUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE, ENGINE_0, ENGINE_1);
}

NGMotionUnitControl::NGMotionUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE, ENGINE_0, ENGINE_1);
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE, ENGINE_0, ENGINE_1);
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate, ENGINE_0, ENGINE_1);
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address, int serialRate, int engineLeft, int engineRight) {
    _create(name, address, serialRate, engineLeft, engineRight);
}

void NGMotionUnitControl::_create(char* name, byte address, int serialRate, int engineLeft, int engineRight) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    _steeringControl = new NGSteeringControl(engineLeft, engineRight);
    Wire.begin(_address);
    //Wire.onReceive(_unitWireReceiveEvent);
    //Wire.onRequest(_unitWireRequestEvent);
}

void NGMotionUnitControl::_processingReceivedData() {
    
}

void NGMotionUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    _steeringControl->initialize();
    _steeringControl->stop();
    _initialized = true;
    if (_logging) {
        char log[100];
        sprintf(log, "...Unit \"%s\" with steering initialized", _name );
        writeInfo(log);
    }
    _writeState();
}

void NGMotionUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
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

void NGMotionUnitControl::requestData(byte* data) {
    
}
