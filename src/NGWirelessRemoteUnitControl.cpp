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

void NGWirelessRemoteUnitControl::initialize() {
    NGCustomUnitControl::initialize();
}

void NGWirelessRemoteUnitControl::processingLoop() {
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

void NGWirelessRemoteUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}
