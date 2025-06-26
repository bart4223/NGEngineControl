//
//  NGSymbolCircleLEDStripEffect.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 26.06.25.
//

#include <Effects/NGSymbolCircleLEDStripEffect.h>

NGSymbolCircleLEDStripEffect::NGSymbolCircleLEDStripEffect(NGCircleLEDStrip *circleLEDStrip) {
     _create(circleLEDStrip, syclsekNone);
}

NGSymbolCircleLEDStripEffect::NGSymbolCircleLEDStripEffect(NGCircleLEDStrip *circleLEDStrip, symbolCircleLEDStripEffectKind kind) {
    _create(circleLEDStrip, kind);
}

void NGSymbolCircleLEDStripEffect::_create(NGCircleLEDStrip *circleLEDStrip, symbolCircleLEDStripEffectKind kind) {
    _circleLEDStrip = circleLEDStrip;
    _kind = kind;
}

void NGSymbolCircleLEDStripEffect::_render() {
    _circleLEDStrip->beginUpdate();
    switch(_kind) {
        case syclsekOnAir:
            switch(_currentStep[0]) {
                case 0:
                    _circleLEDStrip->clear();
                    _circleLEDStrip->drawCircleSection(0, 0, 2, 0, 90, COLOR_PURPLE);
                    _circleLEDStrip->drawCircleSection(0, 0, 2, 180, 360, COLOR_PURPLE);
                    _currentStep[0]++;
                    break;
                case 1:
                    _circleLEDStrip->drawCircleSection(0, 0, 3, 45, 155, COLOR_WHITE);
                    _circleLEDStrip->drawCircleSection(0, 0, 3, 235, 335, COLOR_WHITE);
                    _currentStep[0]++;
                    break;
                case 2:
                    _circleLEDStrip->drawCircleSection(0, 0, 5, 45, 145, COLOR_WHITE);
                    _circleLEDStrip->drawCircleSection(0, 0, 5, 225, 325, COLOR_WHITE);
                    _currentStep[0]++;
                    break;
                case 3:
                    _circleLEDStrip->drawCircleSection(0, 0, 7, 45, 135, COLOR_WHITE);
                    _circleLEDStrip->drawCircleSection(0, 0, 7, 225, 315, COLOR_WHITE);
                    _currentStep[0] = 0;
                    break;
            }
            break;
        case syclsekNone:
            _circleLEDStrip->clear();
            break;
    }   
    _circleLEDStrip->endUpdate();
}

int NGSymbolCircleLEDStripEffect::_getRadius() {
    return _circleLEDStrip->getRadiusCount();
}

void NGSymbolCircleLEDStripEffect::initialize() {
    _circleLEDStrip->initialize();
    for (int i = 0; i < _currentStepCount; i++) {
        _currentStep[i] = 0;
    }
    _lastStep = millis();
}

void NGSymbolCircleLEDStripEffect::setStepDelay(int stepdelay) {
    _stepDelay = stepdelay;
}

int NGSymbolCircleLEDStripEffect::getStepDelay() {
    return _stepDelay;
}

void NGSymbolCircleLEDStripEffect::processingLoop() {
    if ((millis() - _lastStep) >= _stepDelay) {
        _render();
        _lastStep = millis();
    }
}