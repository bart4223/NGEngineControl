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
    return registerEffect(effect, false);
}

byte NGiGlassesUnitControl::registerEffect(NGIGlassesEffect *effect, bool hotEffect) {
    if (_effectCount < MAXEFFECTCOUNT) {
        int res = _effectCount;
        glassesEffectItem gei;
        gei.effect = effect;
        _effects[res] = gei;
        _effectCount++;
        if (hotEffect) {
            _hotEffectIndex = res;
        }
        return res;
    } else {
        _raiseException(ExceptionTooMuchEffectCount);
    }
    return -1;
}

void NGiGlassesUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    for (int i = 0; i < _effectCount; i++) {
        _effects[i].effect->initialize();
    }
}

void NGiGlassesUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    if (isEffectRunning()) {
        if (_currentEffectIndex >= 0 && _currentEffectIndex < _effectCount) {
            _effects[_currentEffectIndex].effect->processingLoop();
        }
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

void NGiGlassesUnitControl::firstEffect() {
    if (_effectCount > 0) {
        setCurrentEffect(0);
    }
}

void NGiGlassesUnitControl::nextEffect() {
    if (_effectCount > 0) {
        int nextIndex = _currentEffectIndex + 1;
        if (nextIndex >= _effectCount) {
            nextIndex = 0;
        }
        setCurrentEffect(nextIndex);
    }
}

void NGiGlassesUnitControl::hotEffect() {
    if (_hotEffectIndex > NOHOTEFFECT && _hotEffectIndex < _effectCount) {
        setCurrentEffect(_hotEffectIndex);
    }
}

bool NGiGlassesUnitControl::hasCurrentEffect() {
    return _currentEffectIndex != NOCURRENTEFFECT;
}

 void NGiGlassesUnitControl::startEffectRunning() {
    _effectRunning = true;
 }

void NGiGlassesUnitControl::stopEffectRunning() {
    _effectRunning = false;
 }

void NGiGlassesUnitControl::toggleEffectRunning() {
    if (isEffectRunning()) {
        stopEffectRunning();
    } else {
        startEffectRunning();
    }
 }

 bool NGiGlassesUnitControl::isEffectRunning() {
    return _effectRunning;
 }