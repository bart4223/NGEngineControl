//
//  NGSimpleColorLEDStripEffect.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 01.03.25.
//

#include <NGCommon.h>
#include <Effects/NGSimpleColorLEDStripEffect.h>

NGSimpleColorLEDStripEffect::NGSimpleColorLEDStripEffect(NGColorLEDStrip *LEDStrip) {
    _create(LEDStrip, slsekNone);
}

NGSimpleColorLEDStripEffect::NGSimpleColorLEDStripEffect(NGColorLEDStrip *LEDStrip, simpleLEDStripEffectKind kind) {
     _create(LEDStrip, kind);
}

void NGSimpleColorLEDStripEffect::_create(NGColorLEDStrip *LEDStrip, simpleLEDStripEffectKind kind) {
    _LEDStrip = LEDStrip;
    _kind = kind;
}

void NGSimpleColorLEDStripEffect::_render() {
    _LEDStrip->beginUpdate();
    switch(_kind) {
        case slsekNone:
            _LEDStrip->setBackground(_colorOff);
            _LEDStrip->clear();
            break;
        case slsekFlash:
            if (_currentStep % 2 == 0) {
                _LEDStrip->setBackground(_colorOn);
                _LEDStrip->clear();
            } else {
                _LEDStrip->setBackground(_colorOff);
                _LEDStrip->clear();
            }
            _currentStep++;
            if (_currentStep >= 2) {
                _currentStep = 0;
            }
            break;
        case slsekAlternate:
            for (int y = 0; y < _LEDStrip->getHeight(); y++) {
                for (int x = 0; x < _LEDStrip->getWidth(); x++) {
                    if ((_currentStep + x) % 2 == 0) {
                        _LEDStrip->drawPoint(x, y, _colorOn);
                    } else {
                        _LEDStrip->drawPoint(x, y, _colorOff);
                    }                
                }
            }
            _currentStep++;
            if (_currentStep >= 2) {
                _currentStep = 0;
            }
            break;
        case slsekRunning:
            for (int y = 0; y < _LEDStrip->getHeight(); y++) {
                for (int x = 0; x < _LEDStrip->getWidth(); x++) {
                    if (x == _currentStep) {
                        _LEDStrip->drawPoint(x, y, _colorOn);                      
                    } else {
                        _LEDStrip->drawPoint(x, y, _colorOff);
                    }           
                }
            }
            _currentStep++;
            if (_currentStep >= _LEDStrip->getWidth()) {
                _currentStep = 0;
            }
            break;
        case slsekRandom:
            for (int y = 0; y < _LEDStrip->getHeight(); y++) {
                for (int x = 0; x < _LEDStrip->getWidth(); x++) {
                    if (getYesOrNo()) {
                        _LEDStrip->drawPoint(x, y, _colorOn);                      
                    } else {
                        _LEDStrip->drawPoint(x, y, _colorOff);
                    }           
                }
            }
            break;
    }
    _LEDStrip->endUpdate();
}

void NGSimpleColorLEDStripEffect::setKind(simpleLEDStripEffectKind kind) {
    _kind = kind;
}

void NGSimpleColorLEDStripEffect::setStepDelay(int stepdelay) {
    _stepDelay = stepdelay;
}

int NGSimpleColorLEDStripEffect::getStepDelay() {
    return _stepDelay;
}

void NGSimpleColorLEDStripEffect::setEffectColors(colorRGB colorOn) {
    setEffectColors(colorOn, COLOR_BLACK);
}

void NGSimpleColorLEDStripEffect::setEffectColors(colorRGB colorOn, colorRGB colorOff) {
    _colorOn = colorOn;
    _colorOff = colorOff;
}

void NGSimpleColorLEDStripEffect::initialize() {
    _LEDStrip->initialize();
    _lastStep = millis();
}

void NGSimpleColorLEDStripEffect::processingLoop() {
    if ((millis() - _lastStep) >= _stepDelay) {
        _render();
        _lastStep = millis();
    }
}