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
            if (_currentStep[0] % 2 == 0) {
                _LEDStrip->setBackground(_colorOn);
                _LEDStrip->clear();
            } else {
                _LEDStrip->setBackground(_colorOff);
                _LEDStrip->clear();
            }
            _currentStep[0]++;
            if (_currentStep[0] >= 2) {
                _currentStep[0] = 0;
            }
            break;
        case slsekAlternate:
            for (int y = 0; y < _LEDStrip->getHeight(); y++) {
                for (int x = 0; x < _LEDStrip->getWidth(); x++) {
                    if ((_currentStep[0] + x) % 2 == 0) {
                        _LEDStrip->drawPoint(x, y, _colorOn);
                    } else {
                        _LEDStrip->drawPoint(x, y, _colorOff);
                    }                
                }
            }
            _currentStep[0]++;
            if (_currentStep[0] >= 2) {
                _currentStep[0] = 0;
            }
            break;
        case slsekRunning:
        case slsekRainbow:
            for (int y = 0; y < _LEDStrip->getHeight(); y++) {
                for (int x = 0; x < _LEDStrip->getWidth(); x++) {
                    int i;
                    bool draw = false;
                    for (i = 0; i < _currentStepCount; i++) {
                        draw = x == _currentStep[i];
                        if (draw) {
                            break;
                        }
                    }
                    if (draw) {
                        if (_kind == slsekRainbow) {
                            _LEDStrip->drawPoint(x, y, _currentColor[i]);                      
                        } else {
                            _LEDStrip->drawPoint(x, y, _colorOn); 
                        }
                    } else {
                        _LEDStrip->drawPoint(x, y, _colorOff);
                    }           
                }
            }
            for (int i = 0; i < _currentStepCount; i++) {
                _currentStep[i]++;
                if (_currentStep[i] >= _LEDStrip->getWidth()) {
                    _currentStep[i] = 0;
                }
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

void NGSimpleColorLEDStripEffect::setCurrentStepCount(int currentstepcount) {
    _currentStepCount = currentstepcount;
    if (_currentStepCount > MAXCURRENTSTEPS) {
        _currentStepCount = MAXCURRENTSTEPS;
    }
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
    int index = 0;
    for (int i = 0; i < _currentStepCount; i++) {
        _currentStep[i] = index;
        switch (i) {
            case 0:
            case 6:
                _currentColor[i] = COLOR_GREEN;
                break;
            case 1:
            case 7:
                _currentColor[i] = COLOR_YELLOW;
                break;
            case 2:
            case 8:
                _currentColor[i] = COLOR_ORANGE;
                break;
            case 3:
            case 9:
                _currentColor[i] = COLOR_RED;
                break;
            case 4:
                _currentColor[i] = COLOR_PURPLE;
                break;
            case 5:
                _currentColor[i] = COLOR_BLUE;
                break;
        }
        index--;
    }
    _lastStep = millis();
}

void NGSimpleColorLEDStripEffect::processingLoop() {
    if ((millis() - _lastStep) >= _stepDelay) {
        _render();
        _lastStep = millis();
    }
}