//
//  NGColorDotMatrixBinaryDigit.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.10.22.
//

#include "NGColorDotMatrixBinaryDigit.h"

NGColorDotMatrixBinaryDigit::NGColorDotMatrixBinaryDigit(NGColorDotMatrix *cdm) {
    _create(cdm, DEFARITY, DEFBINARYDIGITDIRECTION, 0, 0);
}

NGColorDotMatrixBinaryDigit::NGColorDotMatrixBinaryDigit(NGColorDotMatrix *cdm, byte posX, byte posY) {
    _create(cdm, DEFARITY, DEFBINARYDIGITDIRECTION, posX, posY);
}

NGColorDotMatrixBinaryDigit::NGColorDotMatrixBinaryDigit(NGColorDotMatrix *cdm, byte arity, byte posX, byte posY) {
    _create(cdm, arity, DEFBINARYDIGITDIRECTION, posX, posY);
}
NGColorDotMatrixBinaryDigit::NGColorDotMatrixBinaryDigit(NGColorDotMatrix *cdm, byte arity) {
    _create(cdm, arity, DEFBINARYDIGITDIRECTION, 0, 0);
}

NGColorDotMatrixBinaryDigit::NGColorDotMatrixBinaryDigit(NGColorDotMatrix *cdm, byte arity, BinaryDigitDirection direction) {
    _create(cdm, arity, direction, 0, 0);
}

NGColorDotMatrixBinaryDigit::NGColorDotMatrixBinaryDigit(NGColorDotMatrix *cdm, byte arity, BinaryDigitDirection direction, byte posX, byte posY) {
    _create(cdm, arity, direction, posX, posY);
}

void NGColorDotMatrixBinaryDigit::_create(NGColorDotMatrix *cdm, byte arity, BinaryDigitDirection direction, byte posX, byte posY) {
    _cdm = cdm;
    _arity = arity;
    _direction = direction;
    _posX = posX;
    _posY = posY;
}

void NGColorDotMatrixBinaryDigit::_render() {
    byte x = 0x01;
    _cdm->beginUpdate();
    switch(_direction) {
        case bddUp:
            for (byte i = 0; i < _arity; i++) {
                if ((_value & x) != 0x00) {
                    _cdm->drawPoint(_posX, _posY - i, _colorOn);
                } else {
                    _cdm->drawPoint(_posX, _posY - i, _colorOff);
                }
                x = x << 1;
            }
            break;
        case bddDown:
            for (byte i = 0; i < _arity; i++) {
                if ((_value & x) != 0x00) {
                    _cdm->drawPoint(_posX, _posY + i, _colorOn);
                } else {
                    _cdm->drawPoint(_posX, _posY + i, _colorOff);
                }
                x = x << 1;
            }
            break;
        case bddLeft:
            for (byte i = 0; i < _arity; i++) {
                if ((_value & x) != 0x00) {
                    _cdm->drawPoint(_posX + i, _posY, _colorOn);
                } else {
                    _cdm->drawPoint(_posX + i, _posY, _colorOff);
                }
                x = x << 1;
            }
            break;
        case bddRight:
            for (byte i = 0; i < _arity; i++) {
                if ((_value & x) != 0x00) {
                    _cdm->drawPoint(_posX - i, _posY, _colorOn);
                } else {
                    _cdm->drawPoint(_posX - i, _posY, _colorOff);
                }
                x = x << 1;
            }
            break;
    }
    _cdm->endUpdate();
}

void NGColorDotMatrixBinaryDigit::setColorOff(colorRGB color) {
    _colorOff = color;
}

void NGColorDotMatrixBinaryDigit::setColorOn(colorRGB color) {
    _colorOn = color;
}

void NGColorDotMatrixBinaryDigit::setValue(byte value) {
    _value = value;
    _render();
}
