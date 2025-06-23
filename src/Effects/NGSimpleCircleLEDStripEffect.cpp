//
//  NGSimpleCircleLEDStripEffect.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 23.06.25.
//

#include <Effects/NGSimpleCircleLEDStripEffect.h>

NGSimpleCircleLEDStripEffect::NGSimpleCircleLEDStripEffect(NGCircleLEDStrip *circleLEDStrip) {
     _create(circleLEDStrip, sclsekNone);
}

NGSimpleCircleLEDStripEffect::NGSimpleCircleLEDStripEffect(NGCircleLEDStrip *circleLEDStrip, simpleCircleLEDStripEffectKind kind) {
    _create(circleLEDStrip, kind);
}

void NGSimpleCircleLEDStripEffect::_create(NGCircleLEDStrip *circleLEDStrip, simpleCircleLEDStripEffectKind kind) {
    _circleLEDStrip = circleLEDStrip;
    _kind = kind;
}

void NGSimpleCircleLEDStripEffect::_render() {
    _circleLEDStrip->beginUpdate();
    switch(_kind) {
        case sclsekPulse:
            _clear();
            _circleLEDStrip->drawCircle(0, 0, _currentStep[0], _colorOn);
            _currentStep[0]++;
            if (_currentStep[0] > _circleLEDStrip->getRadiusCount()) {
                _currentStep[0] = 0;
            }
            break;   
        case sclsekNone:
            _circleLEDStrip->clear();
            break;
    }   
    _circleLEDStrip->endUpdate();
}

void NGSimpleCircleLEDStripEffect::_clear() {
    _circleLEDStrip->beginUpdate();
    for(int i = 1; i <= _circleLEDStrip->getRadiusCount(); i++) {
        _circleLEDStrip->drawCircle(0, 0, i, _colorOff);
    }
    _circleLEDStrip->endUpdate();
}

void NGSimpleCircleLEDStripEffect::initialize() {
    _circleLEDStrip->initialize();
    for (int i = 0; i < _currentStepCount; i++) {
        _currentStep[i] = 0;
    }
    _lastStep = millis();
}

void NGSimpleCircleLEDStripEffect::setStepDelay(int stepdelay) {
    _stepDelay = stepdelay;
}

int NGSimpleCircleLEDStripEffect::getStepDelay() {
    return _stepDelay;
}

void NGSimpleCircleLEDStripEffect::setEffectColors(colorRGB colorOn) {
    setEffectColors(colorOn, COLOR_BLACK);
}

void NGSimpleCircleLEDStripEffect::setEffectColors(colorRGB colorOn, colorRGB colorOff) {
    _colorOn = colorOn;
    _colorOff = colorOff;
}

void NGSimpleCircleLEDStripEffect::processingLoop() {
    if ((millis() - _lastStep) >= _stepDelay) {
        _render();
        _lastStep = millis();
    }
}