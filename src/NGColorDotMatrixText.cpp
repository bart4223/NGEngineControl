//
//  NGColorDotMatrixText.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 23.04.24.
//

#include "NGStrings.h"
#include "NGColorDotMatrixText.h"

NGColorDotMatrixText::NGColorDotMatrixText(NGIPaintableComponent *ipc) {
    _create(ipc);
}

void NGColorDotMatrixText::_create(NGIPaintableComponent *ipc) {
    _digit = new NGColorDotMatrixCharDigit(ipc);
}

void NGColorDotMatrixText::setFont(NGCustomFont *font) {
    _digit->setFont(font);
}

NGCustomFont* NGColorDotMatrixText::getFont() {
    return _digit->getFont();
}

void NGColorDotMatrixText::setColorBackground(colorRGB color) {
    _digit->setColorBackground(color);
}

colorRGB NGColorDotMatrixText::getColorBackground() {
    return _digit->getColorBackground();
}

void NGColorDotMatrixText::setColor(colorRGB color) {
    _digit->setColor(color);
}

colorRGB NGColorDotMatrixText::getColor() {
    return _digit->getColor();
}

void NGColorDotMatrixText::setText(char* text) {
    bool isunicode = false;
    byte unicodes = 0x00;
    for (int i = 0; i < getSize(text); i++) {
        char c = text[i];
        byte b = text[i];
        if (!isunicode) {
            isunicode = b >= 0x80;
        } else {
            unicodes++;
            switch(b) {
                case 0xA9:
                    c = '©'; // 0xC2 0xA9
                    break;
                default:
                    c = ' ';
                    break;
            }
            isunicode = false;
        }
        if (!isunicode) {
            int x = (_posX + i - unicodes) * _digit->PIXELCOUNT;
            int y = 0;
            if (_wrapText) {
                int width = _digit->getPaintableComponent()->getWidth() / _digit->getScale();
                if (x >= width) {
                    byte x2 = x % width;
                    y = x / width;
                    x = x2;
                }
            }
            y = _posY + y * _digit->PIXELCOUNT;
            _digit->beginUpdate();
            _digit->setPosX(x);
            _digit->setPosY(y);
            _digit->setChar(c);
            _digit->endUpdate();
        }
    }
}

void NGColorDotMatrixText::setWrapText(bool wraptext) {
    _wrapText = wraptext;
}

bool NGColorDotMatrixText::getWrapText() {
    return _wrapText;
}

void NGColorDotMatrixText::setPosX(byte posx) {
    _posX = posx;
}

void NGColorDotMatrixText::setPosY(byte posy) {
    _posY = posy;
}
