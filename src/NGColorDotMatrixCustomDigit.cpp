//
//  NGColorDotMatrixCustomDigit.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 21.04.24.
//

#include "NGCommon.h"
#include "NGColorDotMatrixCustomDigit.h"

void NGColorDotMatrixCustomDigit::_create(NGIPaintableComponent *ipc, byte posX, byte posY) {
    _ipc = ipc;
    _posX = posX;
    _posY = posY;
}

NGCustomFont* NGColorDotMatrixCustomDigit::_getFont() {
    NGCustomFont *res = _font;
    if (res == nullptr) {
        res = getGlobalFont();
    }
    return res;
}

void NGColorDotMatrixCustomDigit::_render() {
    NGCustomFont *font = _getFont();
    _ipc->beginUpdate();
    for (int y = 0; y < 8; y++) {
        byte num = font->getCharLineValue(_value, y);
        byte col = 0x01;
        for (int x = 7; x >= 0; x--) {
            if ((num & col) != 0) {
                if (_randomColor) {
                    colorRGB c;
                    c.red = random(0, 256);
                    c.green = random(0, 256);
                    c.blue = random(0, 256);
                    _ipc->drawPoint(_posX + x, _posY + y, c);
                } else {
                    _ipc->drawPoint(_posX + x, _posY + y, _color);
                }
            } else {
                if (_randomColorBackground) {
                    colorRGB c;
                    c.red = random(0, 256);
                    c.green = random(0, 256);
                    c.blue = random(0, 256);
                    _ipc->drawPoint(_posX + x, _posY + y, c);
                } else {
                    _ipc->drawPoint(_posX + x, _posY + y, _colorBackground);
                }
            }
            col = col << 1;
        }
    }
    _ipc->endUpdate();
}

void NGColorDotMatrixCustomDigit::beginUpdate() {
    _updateCount++;
}

void NGColorDotMatrixCustomDigit::endUpdate() {
    if (_updateCount > 0) {
        _updateCount--;
    }
    if (_updateCount == 0) {
        _render();
    }
}

void NGColorDotMatrixCustomDigit::setRandomColorBackground(bool randomcolor) {
    _randomColorBackground = randomcolor;
}

void NGColorDotMatrixCustomDigit::setColorBackground(colorRGB color) {
    _colorBackground = color;
}

colorRGB NGColorDotMatrixCustomDigit::getColorBackground() {
    return _colorBackground;
}

void NGColorDotMatrixCustomDigit::setRandomColor(bool randomcolor) {
    _randomColor = randomcolor;
}

void NGColorDotMatrixCustomDigit::setColor(colorRGB color) {
    _color = color;
}

colorRGB NGColorDotMatrixCustomDigit::getColor() {
    return _color;
}

void NGColorDotMatrixCustomDigit::setFont(NGCustomFont *font) {
    _font = font;
}

NGCustomFont* NGColorDotMatrixCustomDigit::getFont() {
    return _font;
}

void NGColorDotMatrixCustomDigit::setChar(char value) {
    _value = value;
    if (_updateCount == 0) {
        _render();
    }
}

void NGColorDotMatrixCustomDigit::setPosX(int x) {
    _posX = x;
    if (_updateCount == 0) {
        _render();
    }
}

int NGColorDotMatrixCustomDigit::getPosX() {
    return _posX;
}

void NGColorDotMatrixCustomDigit::setPosY(int y) {
    _posY = y;
    if (_updateCount == 0) {
        _render();
    }
}

int NGColorDotMatrixCustomDigit::getPosY() {
    return _posY;
}

int NGColorDotMatrixCustomDigit::getScale() {
    return _ipc->getScale();
}
