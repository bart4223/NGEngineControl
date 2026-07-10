//
//  NGGlassesLEDStripEffect.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 10.06.26.
//

#include <Effects/NGGlassesLEDStripEffect.h>

NGGlassesLEDStripEffect::NGGlassesLEDStripEffect(NGColorLEDStrip *colorLEDStrip) {
     _create(colorLEDStrip, DEFAULTGLASSESLEDSTRIPEFFECTKIND);
}

NGGlassesLEDStripEffect::NGGlassesLEDStripEffect(NGColorLEDStrip *colorLEDStrip, glassesLEDStripEffectKind kind) {
    _create(colorLEDStrip, kind);
}

void NGGlassesLEDStripEffect::_create(NGColorLEDStrip *colorLEDStrip, glassesLEDStripEffectKind kind) {
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
            _colorLEDStrip->clear();
            break;
    }
    _colorLEDStrip->endUpdate();
}

void NGGlassesLEDStripEffect::initialize() {
    _colorLEDStrip->initialize();
    reset();
}

void NGGlassesLEDStripEffect::reset() {
    _colorLEDStrip->clear();
}

void NGGlassesLEDStripEffect::setKind(glassesLEDStripEffectKind kind) {
    _kind = kind;
}

void NGGlassesLEDStripEffect::setColor(colorRGB color) {
    _colorLEDStrip->setBackground(color);
}

void NGGlassesLEDStripEffect::processingLoop() {
    _render();
}