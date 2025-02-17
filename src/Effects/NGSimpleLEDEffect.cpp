//
//  NGSimpleLEDEffect.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 16.01.25.
//

#include <Effects/NGSimpleLEDEffect.h>

NGSimpleLEDEffect::NGSimpleLEDEffect() {
    _create();
}

void NGSimpleLEDEffect::_create() {

}

void NGSimpleLEDEffect::_render() {
    switch(_kind) {
        case slekAlternate:
            for (int i = 0; i < _simpleLEDCount; i++) {
                if (i == _currentStep) {
                    _simpleLEDs[i].LED->on();
                } else {
                    _simpleLEDs[i].LED->off();
                }
            }
            _currentStep++;
            if (_currentStep >= _simpleLEDCount) {
                _currentStep = 0;
            }
            break;
    }
}

void NGSimpleLEDEffect::initialize() {
    _lastStep = millis();
    for (int i = 0; i < _simpleLEDCount; i++) {
         _simpleLEDs[i].LED->initialize();
    }
}

byte NGSimpleLEDEffect::registerLED(NGSimpleLED *led) {
    byte res = _simpleLEDCount;
    if (_simpleLEDCount < MAXSIMPLELEDEFFECTCOUNT) {
        simpleLEDEffect sle;
        sle.LED = led;
        _simpleLEDs[res] = sle;
        _simpleLEDCount++;
    }
    return res;
}

void NGSimpleLEDEffect::setStepDelay(int stepdelay) {
    _stepDelay = stepdelay;
}

void NGSimpleLEDEffect::processingLoop() {
    if (_effectOn) {
        if ((millis() - _lastStep) >= _stepDelay) {
            _render();
            _lastStep = millis();
        }
    } 
}

void NGSimpleLEDEffect::effectOn() {
    if (!_effectOn) {
        _effectOn = true;
        _render();
    }
}

void NGSimpleLEDEffect::effectOff() {
    if (_effectOn) {
        _effectOn = false;
        _currentStep = 0;
        for (int i = 0; i < _simpleLEDCount; i++) {
            if (_simpleLEDs[i].LED->isOn()) {
                _simpleLEDs[i].LED->off();
            }
        }
    }
}