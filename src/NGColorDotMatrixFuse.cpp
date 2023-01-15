//
//  NGColorDotMatrixFuse.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 15.01.23.
//

#include "NGColorDotMatrixFuse.h"

NGColorDotMatrixFuse::NGColorDotMatrixFuse(NGColorDotMatrix *cdm) {
    _create(cdm, DEFARITY, DEFFUSEDIRECTION, 0, 0);
}

NGColorDotMatrixFuse::NGColorDotMatrixFuse(NGColorDotMatrix *cdm, byte arity) {
    _create(cdm, arity, DEFFUSEDIRECTION, 0, 0);
}

NGColorDotMatrixFuse::NGColorDotMatrixFuse(NGColorDotMatrix *cdm, byte arity, byte posX, byte posY) {
    _create(cdm, arity, DEFFUSEDIRECTION, posX, posY);
}

NGColorDotMatrixFuse::NGColorDotMatrixFuse(NGColorDotMatrix *cdm, byte arity, FuseDirection direction, byte posX, byte posY) {
    _create(cdm, arity, direction, posX, posY);
}

void NGColorDotMatrixFuse::_create(NGColorDotMatrix *cdm, byte arity, FuseDirection direction, byte posX, byte posY) {
    _cdm = cdm;
    _arity = arity;
    _direction = direction;
    _posX = posX;
    _posY = posY;
}

void NGColorDotMatrixFuse::_render() {
    _cdm->beginUpdate();
    switch(_direction) {
        case fdUp:
            for (int i = 0; i < _arity; i++) {
                if (i < _value) {
                    _cdm->drawPoint(_posX, _posY + i, _colorOn);

                } else {
                    _cdm->drawPoint(_posX, _posY + i, _colorOff);
                }
            }
            break;
        case fdDown:
            for (int i = 0; i < _arity; i++) {
                if (i < _value) {
                    _cdm->drawPoint(_posX, _posY - i, _colorOn);

                } else {
                    _cdm->drawPoint(_posX, _posY - i, _colorOff);
                }
            }
            break;
        case fdLeft:
            for (int i = 0; i < _arity; i++) {
                if (i < _value) {
                    _cdm->drawPoint(_posX + i, _posY, _colorOn);

                } else {
                    _cdm->drawPoint(_posX + i, _posY, _colorOff);
                }
            }
            break;
        case fdRight:
            for (int i = 0; i < _arity; i++) {
                if (i < _value) {
                    _cdm->drawPoint(_posX - i, _posY, _colorOn);

                } else {
                    _cdm->drawPoint(_posX - i, _posY, _colorOff);
                }
            }
            break;
    }
    _cdm->endUpdate();
}

void NGColorDotMatrixFuse::setColorOff(colorRGB color) {
    _colorOff = color;
}

void NGColorDotMatrixFuse::setColorOn(colorRGB color) {
    _colorOn = color;
}

void NGColorDotMatrixFuse::setValue(byte value) {
    _value = value;
    _render();
}
