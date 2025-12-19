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
                    _circleLEDStrip->drawCircle(0, 0, 2, _colorOne);
                    _currentStep[0]++;
                    break;
                case 1:
                    _circleLEDStrip->drawCircleSection(0, 0, 3, 45, 155, _colorTwo);
                    _circleLEDStrip->drawCircleSection(0, 0, 3, 235, 335, _colorTwo);
                    _currentStep[0]++;
                    break;
                case 2:
                    _circleLEDStrip->drawCircleSection(0, 0, 5, 45, 145, _colorTwo);
                    _circleLEDStrip->drawCircleSection(0, 0, 5, 225, 325, _colorTwo);
                    _currentStep[0]++;
                    break;
                case 3:
                    _circleLEDStrip->drawCircleSection(0, 0, 7, 40, 150, _colorTwo);
                    _circleLEDStrip->drawCircleSection(0, 0, 7, 220, 330, _colorTwo);
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
    reset();
}

void NGSymbolCircleLEDStripEffect::reset() {
    _circleLEDStrip->clear();
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

void NGSymbolCircleLEDStripEffect::setSymbolColors(colorRGB colorOne, colorRGB colorTwo) {
    _colorOne = colorOne;
    _colorTwo = colorTwo;
}

void NGSymbolCircleLEDStripEffect::processingLoop() {
    if ((millis() - _lastStep) >= _stepDelay) {
        _render();
        _lastStep = millis();
    }
}