//
//  NGGlassesLEDStripEffect.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 10.07.26.
//

#include <NGCommon.h>
#include <Effects/NGGlassesLEDStripEffect.h>

NGGlassesLEDStripEffect::NGGlassesLEDStripEffect(NGColorLEDStrip *colorLEDStrip) {
     _create(colorLEDStrip, DEFAULTGLASSESLEDSTRIPEFFECTKIND);
}

NGGlassesLEDStripEffect::NGGlassesLEDStripEffect(NGColorLEDStrip *colorLEDStrip, glassesEffectKind kind) {
    _create(colorLEDStrip, kind);
}

void NGGlassesLEDStripEffect::_create(NGColorLEDStrip *colorLEDStrip, glassesEffectKind kind) {
    _colorLEDStrip = colorLEDStrip;
    _kind = kind;
}

void NGGlassesLEDStripEffect::_render() {
    _colorLEDStrip->beginUpdate();
    switch (_kind) {
        case glekNone:
            _colorLEDStrip->setBackground(COLOR_BLACK);
            _colorLEDStrip->clear();
            break;
        case glekSolid:
            _colorLEDStrip->setBackground(_color);
            _colorLEDStrip->clear();
            break;
        case glekRotateOne:
        case glekRotateTwo:
        case glekRotateThree:
        case glekOppositeRotateOne:
        case glekOppositeRotateTwo:
        case glekOppositeRotateThree:
            _colorLEDStrip->setBackground(COLOR_BLACK);
            _colorLEDStrip->clear();
            _colorLEDStrip->drawPoint(_rotationPosition, 0, _color);
            if (_kind == glekOppositeRotateOne || _kind == glekOppositeRotateTwo || _kind == glekOppositeRotateThree) {
                _colorLEDStrip->drawPoint((_colorLEDStrip->getWidth() - _rotationPosition) % _colorLEDStrip->getWidth(), 1, _color);
            } else {
                _colorLEDStrip->drawPoint(_rotationPosition, 1, _color);
            }
            if (_kind == glekRotateTwo || _kind == glekOppositeRotateTwo || _kind == glekRotateThree || _kind == glekOppositeRotateThree) {
                _colorLEDStrip->drawPoint((_rotationPosition + 1) % _colorLEDStrip->getWidth(), 0, _color);
                if (_kind == glekOppositeRotateTwo || _kind == glekOppositeRotateThree) {
                    _colorLEDStrip->drawPoint((_colorLEDStrip->getWidth() - (_rotationPosition + 1)) % _colorLEDStrip->getWidth(), 1, _color);
                } else {
                    _colorLEDStrip->drawPoint((_rotationPosition + 1) % _colorLEDStrip->getWidth(), 1, _color);
                }
            }
            if (_kind == glekRotateThree || _kind == glekOppositeRotateThree) {
                _colorLEDStrip->drawPoint((_rotationPosition + 2) % _colorLEDStrip->getWidth(), 0, _color);
                if (_kind == glekOppositeRotateThree) {
                    int x = (_colorLEDStrip->getWidth() - (_rotationPosition + 2));
                    if (x < 0) {
                        x = _colorLEDStrip->getWidth() + x;
                    }
                    x = x % _colorLEDStrip->getWidth();
                    _colorLEDStrip->drawPoint(x, 1, _color);
                } else {
                    _colorLEDStrip->drawPoint((_rotationPosition + 2) % _colorLEDStrip->getWidth(), 1, _color);
                }
            }
            _rotationPosition++;
            if (_rotationPosition >= _colorLEDStrip->getWidth()) {
                _rotationPosition = 0;
            }
            break;
        case glekRandom:
        case glekOppositeRandom:
            _colorLEDStrip->setBackground(COLOR_BLACK);
            _colorLEDStrip->clear();
            for (int x = 0; x < _colorLEDStrip->getWidth(); x++) {
                colorRGB color = _color;
                if (getYesOrNo()) {
                    color = getRandomColor();
                } 
                _colorLEDStrip->drawPoint(x, 0, color);
                if (_kind == glekOppositeRandom) {
                    color = _color;
                    if (getYesOrNo()) {
                        color = getRandomColor();
                    } 
                }
                _colorLEDStrip->drawPoint(x, 1, color);
            }
            break;
    }       
    _colorLEDStrip->endUpdate();
}

void NGGlassesLEDStripEffect::initialize() {
    _colorLEDStrip->initialize();
    reset();
    _lastRenderTime = millis();
    _rotationPosition = 0;
}

void NGGlassesLEDStripEffect::reset() {
    _colorLEDStrip->clear();
}

void NGGlassesLEDStripEffect::setKind(glassesEffectKind kind) {
    _kind = kind;
}

glassesEffectKind NGGlassesLEDStripEffect::getKind() {
    return _kind;
}

void NGGlassesLEDStripEffect::setColor(colorRGB color) {
    _color = color;
}

colorRGB NGGlassesLEDStripEffect::getColor() {
    return _color;
}

void NGGlassesLEDStripEffect::setDelay(int delay) {
    _delay = delay;
}

int NGGlassesLEDStripEffect::getDelay() {
    return _delay;
}

void NGGlassesLEDStripEffect::processingLoop() {
    if (millis() - _lastRenderTime >= _delay) {
        _render();
        _lastRenderTime = millis();
    }
}