//
//  NGColorDotMatrixDecimalDigit.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 02.03.23.
//

#include "NGColorDotMatrixDecimalDigit.h"

NGColorDotMatrixDecimalDigit::NGColorDotMatrixDecimalDigit(NGIPaintableComponent *ipc) {
    _create(ipc, 0, 0);
}

void NGColorDotMatrixDecimalDigit::_create(NGIPaintableComponent *ipc, byte posX, byte posY) {
    _ipc = ipc;
    _posX = posX;
    _posY = posY;
}

byte NGColorDotMatrixDecimalDigit::_getNumeralZero(byte line) {
    byte res = 0x00;
    switch(line) {
        case 0x00:
        case 0x07:
            res = 0x7C;
            break;
        case 0x01:
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x05:
        case 0x06:
            res = 0xCE;
            break;
    }
    return res;
}

byte NGColorDotMatrixDecimalDigit::_getNumeralOne(byte line) {
    byte res = 0x00;
    switch(line) {
        case 0x00:
        case 0x04:
        case 0x05:
        case 0x06:
        case 0x07:
            res = 0x1C;
            break;
        case 0x01:
            res = 0x3C;
            break;
        case 0x02:
            res = 0x7C;
            break;
        case 0x03:
            res = 0xDC;
            break;
    }
    return res;
}

byte NGColorDotMatrixDecimalDigit::_getNumeralTwo(byte line) {
    byte res = 0x00;
    switch(line) {
        case 0x00:
            res = 0x7C;
            break;
        case 0x01:
            res = 0xCE;
            break;
        case 0x02:
            res = 0x8E;
            break;
        case 0x03:
            res = 0x0E;
            break;
        case 0x04:
            res = 0x1C;
            break;
        case 0x05:
            res = 0x30;
            break;
        case 0x06:
            res = 0x60;
            break;
        case 0x07:
            res = 0xFE;
            break;
    }
    return res;
}

byte NGColorDotMatrixDecimalDigit::_getNumeralThree(byte line) {
    byte res = 0x00;
    switch(line) {
        case 0x00:
        case 0x07:
            res = 0x7C;
            break;
        case 0x01:
        case 0x06:
            res = 0xCE;
            break;
        case 0x02:
        case 0x05:
            res = 0x8E;
            break;
        case 0x03:
            res = 0x38;
            break;
        case 0x04:
            res = 0x0E;
            break;
    }
    return res;
}

byte NGColorDotMatrixDecimalDigit::_getNumeralFour(byte line) {
    byte res = 0x00;
    switch(line) {
        case 0x00:
            res = 0x18;
            break;
        case 0x01:
            res = 0x30;
            break;
        case 0x02:
            res = 0x60;
            break;
        case 0x03:
            res = 0xC0;
            break;
        case 0x04:
            res = 0xDC;
            break;
        case 0x05:
            res = 0xFE;
            break;
        case 0x06:
        case 0x07:
            res = 0x1C;
            break;
    }
    return res;
}

byte NGColorDotMatrixDecimalDigit::_getNumeralFive(byte line) {
    byte res = 0x00;
    switch(line) {
        case 0x00:
            res = 0xFE;
            break;
        case 0x01:
        case 0x02:
            res = 0xC0;
            break;
        case 0x03:
            res = 0xFC;
            break;
        case 0x04:
        case 0x05:
            res = 0x0E;
            break;
        case 0x06:
            res = 0x8E;
            break;
        case 0x07:
            res = 0x7C;
            break;
    }
    return res;
}

byte NGColorDotMatrixDecimalDigit::_getNumeralSix(byte line) {
    byte res = 0x00;
    switch(line) {
        case 0x00:
            res = 0x18;
            break;
        case 0x01:
            res = 0x30;
            break;
        case 0x02:
            res = 0x60;
            break;
        case 0x03:
        case 0x07:
            res = 0x7C;
            break;
        case 0x04:
        case 0x05:
        case 0x06:
            res = 0xCE;
            break;
    }
    return res;
}

byte NGColorDotMatrixDecimalDigit::_getNumeralSeven(byte line) {
    byte res = 0x00;
    switch(line) {
        case 0x00:
            res = 0xFE;
            break;
        case 0x01:
        case 0x02:
            res = 0x0E;
            break;
        case 0x03:
            res = 0x0C;
            break;
        case 0x04:
        case 0x05:
            res = 0x18;
            break;
        case 0x06:
            res = 0x30;
            break;
        case 0x07:
            res = 0x60;
            break;
    }
    return res;
}

byte NGColorDotMatrixDecimalDigit::_getNumeralEight(byte line) {
    byte res = 0x00;
    switch(line) {
        case 0x00:
        case 0x03:
        case 0x07:
            res = 0x7C;
            break;
        case 0x01:
        case 0x02:
        case 0x04:
        case 0x05:
        case 0x06:
            res = 0xCE;
            break;
    }
    return res;
}

byte NGColorDotMatrixDecimalDigit::_getNumeralNine(byte line) {
    byte res = 0x00;
    switch(line) {
        case 0x00:
        case 0x04:
            res = 0x7C;
            break;
        case 0x01:
        case 0x02:
        case 0x03:
            res = 0xCE;
            break;
        case 0x05:
            res = 0x0C;
            break;
        case 0x06:
            res = 0x18;
            break;
        case 0x07:
            res = 0x70;
            break;
    }
    return res;
}

void NGColorDotMatrixDecimalDigit::_render() {
    _ipc->beginUpdate();
    for (int y = 0; y < 8; y++) {
        byte num;
        switch(_value) {
            case 0x00:
                num = _getNumeralZero(y);
                break;
            case 0x01:
                num = _getNumeralOne(y);
                break;
            case 0x02:
                num = _getNumeralTwo(y);
                break;
            case 0x03:
                num = _getNumeralThree(y);
                break;
            case 0x04:
                num = _getNumeralFour(y);
                break;
            case 0x05:
                num = _getNumeralFive(y);
                break;
            case 0x06:
                num = _getNumeralSix(y);
                break;
            case 0x07:
                num = _getNumeralSeven(y);
                break;
            case 0x08:
                num = _getNumeralEight(y);
                break;
            case 0x09:
                num = _getNumeralNine(y);
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

void NGColorDotMatrixDecimalDigit::setRandomColorBackground(bool randomcolor) {
    _randomColorBackground = randomcolor;
}

void NGColorDotMatrixDecimalDigit::setColorBackground(colorRGB color) {
    _colorBackground = color;
}

void NGColorDotMatrixDecimalDigit::setRandomColor(bool randomcolor) {
    _randomColor = randomcolor;
}

void NGColorDotMatrixDecimalDigit::setColor(colorRGB color) {
    _color = color;
}

void NGColorDotMatrixDecimalDigit::setValue(byte value) {
    _value = value;
    _render();
}

void NGColorDotMatrixDecimalDigit::setPosX(int x) {
    _posX = x;
    _render();
}

int NGColorDotMatrixDecimalDigit::getPosX() {
    return _posX;
}

void NGColorDotMatrixDecimalDigit::setPosY(int y) {
    _posY = y;
}

int NGColorDotMatrixDecimalDigit::getPosY() {
    return _posY;
    _render();
}
