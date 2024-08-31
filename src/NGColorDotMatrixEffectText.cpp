//
//  NGColorDotMatrixEffectText.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 31.08.24.
//

#include "NGColorDotMatrixEffectText.h"

NGColorDotMatrixEffectText::NGColorDotMatrixEffectText(NGIPaintableComponent *ipc) {
    _create(ipc, COLOR_BLACK, COLOR_BLACK, nullptr);
}

NGColorDotMatrixEffectText::NGColorDotMatrixEffectText(NGIPaintableComponent *ipc, NGCustomFont *font) {
    _create(ipc, COLOR_BLACK, COLOR_BLACK, font);
}

NGColorDotMatrixEffectText::NGColorDotMatrixEffectText(NGIPaintableComponent *ipc, colorRGB color, NGCustomFont *font) {
    _create(ipc, color, COLOR_BLACK, font);
}

NGColorDotMatrixEffectText::NGColorDotMatrixEffectText(NGIPaintableComponent *ipc, colorRGB color, colorRGB colorBackground, NGCustomFont *font) {
    _create(ipc, color, colorBackground, font);
}

void NGColorDotMatrixEffectText::_create(NGIPaintableComponent *ipc, colorRGB color, colorRGB colorBackground, NGCustomFont *font) {
    _charDigit = new NGColorDotMatrixCharDigit(ipc);
    _charDigit->setColor(color);
    _charDigit->setColorBackground(colorBackground);
    if (font != nullptr) {
        _charDigit->setFont(font);
    }
}

void NGColorDotMatrixEffectText::initialize() {
    
}

void NGColorDotMatrixEffectText::setPosition(int posx, int posy) {
    _posX = posx;
    _posY = posy;
}

void NGColorDotMatrixEffectText::setDelay(int delay) {
    _delay = delay;
}

void NGColorDotMatrixEffectText::setText(char *text) {
    _text = text;
}

void NGColorDotMatrixEffectText::processingLoop() {
    if (_lastStep == 0) {
        _lastStep = millis();
    }
    if (_currentPos < strlen(_text)) {
        _charDigit->beginUpdate();
        _charDigit->setPosX(_posX);
        _charDigit->setPosY(_posY);
        _charDigit->setChar(_text[_currentPos]);
        _charDigit->endUpdate();
        if (millis() - _lastStep > _delay) {
            _currentPos++;
            if (_currentPos >= strlen(_text)) {
                _currentPos = 0;
            }
            _lastStep = millis();
        }
    }
}

