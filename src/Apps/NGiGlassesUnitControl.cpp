//
//  NGiGlassesUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 10.07.26.
//

#include <Apps/NGiGlassesUnitControl.h>
#include <NGExceptionDefinitions.h>

NGiGlassesUnitControl::NGiGlassesUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE);
}

NGiGlassesUnitControl::NGiGlassesUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE);
}

NGiGlassesUnitControl::NGiGlassesUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE);
}

NGiGlassesUnitControl::NGiGlassesUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate);
}

void NGiGlassesUnitControl::_create(char* name, byte address, int serialRate) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    Wire.begin(_address);
}

void NGiGlassesUnitControl::_processingReceivedData() {
    
}

void NGiGlassesUnitControl::_processingStartupLoop() {

}

void NGiGlassesUnitControl::_processingIRRemoteData() {
    
}

byte NGiGlassesUnitControl::registerEffect(NGIGlassesEffect *effect) {
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

void NGiGlassesUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    for (int i = 0; i < _effectCount; i++) {
        _effects[i]->initialize();
    }
}

void NGiGlassesUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    if (_currentEffectIndex >= 0 && _currentEffectIndex < _effectCount) {
        _effects[_currentEffectIndex]->processingLoop();
    }
}

void NGiGlassesUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}

void NGiGlassesUnitControl::setCurrentEffect(int effectIndex) {
    if (_currentEffectIndex != effectIndex) {
        _currentEffectIndex = effectIndex;
    }
}

int NGiGlassesUnitControl::getCurrentEffect() {
    return _currentEffectIndex;
}