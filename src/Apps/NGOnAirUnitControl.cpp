//
//  NGOnAirUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.06.25.
//

#include <Apps/NGOnAirUnitControl.h>
#include <NGExceptionDefinitions.h>

NGOnAirUnitControl::NGOnAirUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE);
}

NGOnAirUnitControl::NGOnAirUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE);
}

NGOnAirUnitControl::NGOnAirUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE);
}

NGOnAirUnitControl::NGOnAirUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate);
}

void NGOnAirUnitControl::_create(char* name, byte address, int serialRate) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    Wire.begin(_address);
}

void NGOnAirUnitControl::_processingReceivedData() {
    
}

void NGOnAirUnitControl::_processingStartupLoop() {

}

void NGOnAirUnitControl::_processingIRRemoteData() {
    
}

byte NGOnAirUnitControl::registerEffect(NGIEffect *effect) {
    if (_effectCount < MAXEFFECTCOUNT) {
        int res = _effectCount;
        _effects[res] = effect;
        _effectCount++;
        return res;
    } else {
        _raiseException(ExceptionTooMuchEffectCount);
    }
    return -1;
}

void NGOnAirUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    for (int i = 0; i < _effectCount; i++) {
        _effects[i]->initialize();
    }
}

void NGOnAirUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    if (_currentEffectIndex >= 0 && _currentEffectIndex < _effectCount) {
        _effects[_currentEffectIndex]->processingLoop();
    }
}

void NGOnAirUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}

void NGOnAirUnitControl::setCurrentEffect(int effectIndex) {
    _currentEffectIndex = effectIndex;
}