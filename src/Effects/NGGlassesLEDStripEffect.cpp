//
//  NGGlassesLEDStripEffect.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 10.07.26.
//

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
            for (int x = 0; x < _colorLEDStrip->getWidth(); x++) {
                colorRGB color = COLOR_BLACK;
                if (x == _rotationPosition) {
                    color = _color;
                }
                _colorLEDStrip->drawPoint(x, 0, color);
                if (_kind == glekOppositeRotateOne || _kind == glekOppositeRotateTwo || _kind == glekOppositeRotateThree) {
                    if (x == (_colorLEDStrip->getWidth() - _rotationPosition) || (x == 0 && _rotationPosition == 0)) {
                        color = _color;
                    } else {
                        color = COLOR_BLACK;
                    }
                }
                _colorLEDStrip->drawPoint(x, 1, color);
                switch (_kind) {
                    case glekRotateTwo:
                    case glekRotateThree:
                    case glekOppositeRotateTwo:
                    case glekOppositeRotateThree:
                        if (x == (_rotationPosition + 1) % _colorLEDStrip->getWidth()) {
                            color = _color;
                        }
                        _colorLEDStrip->drawPoint(x, 0, color);
                        if (_kind == glekOppositeRotateTwo || _kind == glekOppositeRotateThree) {
                            if (x == (_colorLEDStrip->getWidth() - 1 - _rotationPosition + 1) % _colorLEDStrip->getWidth()) {
                                color = _color;
                            } else {
                                color = COLOR_BLACK;
                            }
                        }
                        _colorLEDStrip->drawPoint(x, 1, color);
                        switch (_kind) {
                            case glekRotateThree:
                                if (x == (_rotationPosition + 2) % _colorLEDStrip->getWidth()) {
                                    color = _color;
                                }
                                _colorLEDStrip->drawPoint(x, 0, color);
                                _colorLEDStrip->drawPoint(x, 1, color);
                                break;
                        }
                        break;                    
                }
            }
            _rotationPosition++;
            if (_rotationPosition >= _colorLEDStrip->getWidth()) {
                _rotationPosition = 0;
            }
            break;
    }       
    _colorLEDStrip->endUpdate();
}

void NGGlassesLEDStripEffect::initialize() {
    _colorLEDStrip->initialize();
    reset();
    _lastRenderTime = millis();
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