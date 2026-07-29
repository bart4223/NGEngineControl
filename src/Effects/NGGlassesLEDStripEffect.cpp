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
            _colorLEDStrip->setBackground(COLOR_BLACK);
            for (int i = 0; i < _colorLEDStrip->getWidth(); i++) {
                colorRGB color = COLOR_BLACK;
                if (i == _rotationPosition) {
                    color = _color;
                }
                _colorLEDStrip->drawPoint(i, 0, color);
                _colorLEDStrip->drawPoint(i, 1, color);
                switch (_kind) {
                    case glekRotateTwo:
                    case glekRotateThree:
                        if (i == (_rotationPosition + 1) % _colorLEDStrip->getWidth()) {
                            color = _color;
                        }
                        _colorLEDStrip->drawPoint(i, 0, color);
                        _colorLEDStrip->drawPoint(i, 1, color);
                        switch (_kind) {
                            case glekRotateThree:
                                if (i == (_rotationPosition + 2) % _colorLEDStrip->getWidth()) {
                                    color = _color;
                                }
                                _colorLEDStrip->drawPoint(i, 0, color);
                                _colorLEDStrip->drawPoint(i, 1, color);
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