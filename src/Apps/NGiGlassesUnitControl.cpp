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

void NGiGlassesUnitControl::setEffectImplementation(NGIGlassesEffect *effect) {
    _effectImplementation = effect;
}

bool NGiGlassesUnitControl::hasEffectImplementation() {
    return _effectImplementation != nullptr;
}

byte NGiGlassesUnitControl::registerEffect(glassesEffectKind kind) {
    return registerEffect(kind, false);
}

byte NGiGlassesUnitControl::registerEffect(glassesEffectKind kind, int delay) {
    return registerEffect(kind, false, delay);
}

byte NGiGlassesUnitControl::registerEffect(glassesEffectKind kind, bool hotEffect) {
    return registerEffect(kind, hotEffect, 0);
}

byte NGiGlassesUnitControl::registerEffect(glassesEffectKind kind, bool hotEffect, int delay) {
    if (_effectCount < MAXEFFECTCOUNT) {
        int res = _effectCount;
        glassesEffectItem gei;
        gei.kind = kind;
        gei.delay = delay;
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

byte NGiGlassesUnitControl::registerColor(colorRGB color) { 
    if (_colorCount < MAXCOLORCOUNT) {
        int res = _colorCount;
        _colors[res] = color;
        _colorCount++;
        return res;
    } else {
        _raiseException(ExceptionTooMuchColorCount);
    }
    return -1;
}

void NGiGlassesUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    if (hasEffectImplementation()) {
        _effectImplementation->initialize();
    }
}

void NGiGlassesUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    if (isEffectRunning() && hasEffectImplementation()) {
        if (_currentEffectIndex >= 0 && _currentEffectIndex < _effectCount) {
            _effectImplementation->processingLoop();
        }
    }
}

void NGiGlassesUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}

bool NGiGlassesUnitControl::hasEffects() {
    return _effectCount > 0;
}

void NGiGlassesUnitControl::setCurrentEffect(int effectIndex) {
    if (_currentEffectIndex != effectIndex) {
        _currentEffectIndex = effectIndex;
       if (hasEffectImplementation() && _currentEffectIndex >= 0 && _currentEffectIndex < _effectCount) {
            _effectImplementation->setKind(_effects[_currentEffectIndex].kind);
            _effectImplementation->setDelay(_effects[_currentEffectIndex].delay);
            if (hasCurrentColor()) {
                setCurrentColor(_currentColorIndex);
            }
        }
    }
}

int NGiGlassesUnitControl::getCurrentEffect() {
    return _currentEffectIndex;
}

bool NGiGlassesUnitControl::hasCurrentEffect() {
    return _currentEffectIndex != NOCURRENTEFFECT;
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
        if (!isEffectRunning()) {
            startEffectRunning();
        }
    }
}

void NGiGlassesUnitControl::hotEffect() {
    if (_hotEffectIndex > NOHOTEFFECT && _hotEffectIndex < _effectCount) {
        setCurrentEffect(_hotEffectIndex);
        if (!isEffectRunning()) {
            startEffectRunning();
        }
    }
}

bool NGiGlassesUnitControl::hasHotEffect() {
    return _hotEffectIndex > NOHOTEFFECT && _hotEffectIndex < _effectCount;
}

bool NGiGlassesUnitControl::hasColors() {
    return _colorCount > 0;
}

void NGiGlassesUnitControl::setCurrentColor(int colorIndex) {
    if (hasCurrentEffect() && _currentColorIndex != colorIndex) {
        _currentColorIndex = colorIndex;
       if (hasEffectImplementation() && _currentColorIndex >= 0 && _currentColorIndex < _colorCount) {
            _effectImplementation->setColor(_colors[_currentColorIndex]);
        }
    }
}

int NGiGlassesUnitControl::getCurrentColor() {
    return _currentColorIndex;
}

bool NGiGlassesUnitControl::hasCurrentColor() {
    return _currentColorIndex != NOCURRENTCOLOR;
}

void NGiGlassesUnitControl::firstColor() {
    if (_colorCount > 0) {
        setCurrentColor(0);
    }
}

void NGiGlassesUnitControl::nextColor() {
    if (_colorCount > 0) {
        int nextIndex = _currentColorIndex + 1;
        if (nextIndex >= _colorCount) {
            nextIndex = 0;
        }
        setCurrentColor(nextIndex);
    }
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