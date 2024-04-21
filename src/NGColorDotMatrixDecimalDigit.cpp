//
//  NGColorDotMatrixDecimalDigit.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 02.03.23.
//

#include "NGCommon.h"
#include "NGColorDotMatrixDecimalDigit.h"

NGColorDotMatrixDecimalDigit::NGColorDotMatrixDecimalDigit(NGIPaintableComponent *ipc) {
    _create(ipc, 0, 0);
}

void NGColorDotMatrixDecimalDigit::_create(NGIPaintableComponent *ipc, byte posX, byte posY) {
    _ipc = ipc;
    _posX = posX;
    _posY = posY;
}

NGCustomFont* NGColorDotMatrixDecimalDigit::_getFont() {
    NGCustomFont *res = _font;
    if (res == nullptr) {
        res = getGlobalFont();
    }
    return res;
}

void NGColorDotMatrixDecimalDigit::_render() {
    NGCustomFont *font = _getFont();
    _ipc->beginUpdate();
    for (int y = 0; y < 8; y++) {
        byte num;
        switch(_value) {
            case 0x00:
                num = font->getCharLineValue('0', y);
                break;
            case 0x01:
                num = font->getCharLineValue('1', y);
                break;
            case 0x02:
                num = font->getCharLineValue('2', y);
                break;
            case 0x03:
                num = font->getCharLineValue('3', y);
                break;
            case 0x04:
                num = font->getCharLineValue('4', y);
                break;
            case 0x05:
                num = font->getCharLineValue('5', y);
                break;
            case 0x06:
                num = font->getCharLineValue('6', y);
                break;
            case 0x07:
                num = font->getCharLineValue('7', y);
                break;
            case 0x08:
                num = font->getCharLineValue('8', y);
                break;
            case 0x09:
                num = font->getCharLineValue('9', y);
                break;
        }
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

void NGColorDotMatrixDecimalDigit::beginUpdate() {
    _updateCount++;
}

void NGColorDotMatrixDecimalDigit::endUpdate() {
    if (_updateCount > 0) {
        _updateCount--;
    }
    if (_updateCount == 0) {
        _render();
    }
}

void NGColorDotMatrixDecimalDigit::setRandomColorBackground(bool randomcolor) {
    _randomColorBackground = randomcolor;
}

void NGColorDotMatrixDecimalDigit::setColorBackground(colorRGB color) {
    _colorBackground = color;
}

colorRGB NGColorDotMatrixDecimalDigit::getColorBackground() {
    return _colorBackground;
}

void NGColorDotMatrixDecimalDigit::setRandomColor(bool randomcolor) {
    _randomColor = randomcolor;
}

void NGColorDotMatrixDecimalDigit::setColor(colorRGB color) {
    _color = color;
}

colorRGB NGColorDotMatrixDecimalDigit::getColor() {
    return _color;
}

void NGColorDotMatrixDecimalDigit::setFont(NGCustomFont *font) {
    _font = font;
}

NGCustomFont* NGColorDotMatrixDecimalDigit::getFont() {
    return _font;
}

void NGColorDotMatrixDecimalDigit::setValue(byte value) {
    _value = value;
    if (_updateCount == 0) {
        _render();
    }
}

void NGColorDotMatrixDecimalDigit::setPosX(int x) {
    _posX = x;
    if (_updateCount == 0) {
        _render();
    }
}

int NGColorDotMatrixDecimalDigit::getPosX() {
    return _posX;
}

void NGColorDotMatrixDecimalDigit::setPosY(int y) {
    _posY = y;
    if (_updateCount == 0) {
        _render();
    }
}

int NGColorDotMatrixDecimalDigit::getPosY() {
    return _posY;
}

int NGColorDotMatrixDecimalDigit::getScale() {
    return _ipc->getScale();
}
