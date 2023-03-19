//
//  NGColorDotMatrixBinaryDigit.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.10.22.
//

#include "NGColorDotMatrixBinaryDigit.h"

NGColorDotMatrixBinaryDigit::NGColorDotMatrixBinaryDigit(NGIPaintableComponent *ipc) {
    _create(ipc, DEFARITY, DEFBINARYDIGITDIRECTION, 0, 0);
}

NGColorDotMatrixBinaryDigit::NGColorDotMatrixBinaryDigit(NGIPaintableComponent *ipc, byte posX, byte posY) {
    _create(ipc, DEFARITY, DEFBINARYDIGITDIRECTION, posX, posY);
}

NGColorDotMatrixBinaryDigit::NGColorDotMatrixBinaryDigit(NGIPaintableComponent *ipc, byte arity, byte posX, byte posY) {
    _create(ipc, arity, DEFBINARYDIGITDIRECTION, posX, posY);
}
NGColorDotMatrixBinaryDigit::NGColorDotMatrixBinaryDigit(NGIPaintableComponent *ipc, byte arity) {
    _create(ipc, arity, DEFBINARYDIGITDIRECTION, 0, 0);
}

NGColorDotMatrixBinaryDigit::NGColorDotMatrixBinaryDigit(NGIPaintableComponent *ipc, byte arity, BinaryDigitDirection direction) {
    _create(ipc, arity, direction, 0, 0);
}

NGColorDotMatrixBinaryDigit::NGColorDotMatrixBinaryDigit(NGIPaintableComponent *ipc, byte arity, BinaryDigitDirection direction, byte posX, byte posY) {
    _create(ipc, arity, direction, posX, posY);
}

void NGColorDotMatrixBinaryDigit::_create(NGIPaintableComponent *ipc, byte arity, BinaryDigitDirection direction, byte posX, byte posY) {
    _ipc = ipc;
    _arity = arity;
    _direction = direction;
    _posX = posX;
    _posY = posY;
}

void NGColorDotMatrixBinaryDigit::_render() {
    byte x = 0x01;
    _ipc->beginUpdate();
    switch(_direction) {
        case bddUp:
            for (byte i = 0; i < _arity; i++) {
                if ((_value & x) != 0x00) {
                    if (_paintableObjectOn != nullptr) {
                        _paintableObjectOn->render(_posX, _posY - i);
                    } else {
                        _ipc->drawPoint(_posX, _posY - i, _colorOn);
                    }
                } else {
                    if (_paintableObjectOff != nullptr) {
                        _paintableObjectOff->render(_posX, _posY - i);
                    } else {
                        _ipc->drawPoint(_posX, _posY - i, _colorOff);
                    }
                }
                x = x << 1;
            }
            break;
        case bddDown:
            for (byte i = 0; i < _arity; i++) {
                if ((_value & x) != 0x00) {
                    if (_paintableObjectOn != nullptr) {
                        _paintableObjectOn->render(_posX, _posY + i);
                    } else {
                        _ipc->drawPoint(_posX, _posY + i, _colorOn);
                    }
                } else {
                    if (_paintableObjectOff != nullptr) {
                        _paintableObjectOff->render(_posX, _posY + i);
                    } else {
                        _ipc->drawPoint(_posX, _posY + i, _colorOff);
                    }
                }
                x = x << 1;
            }
            break;
        case bddLeft:
            for (byte i = 0; i < _arity; i++) {
                if ((_value & x) != 0x00) {
                    if (_paintableObjectOn != nullptr) {
                        _paintableObjectOn->render(_posX + i, _posY);
                    } else {
                        _ipc->drawPoint(_posX + i, _posY, _colorOn);
                    }
                } else {
                    if (_paintableObjectOff != nullptr) {
                        _paintableObjectOff->render(_posX + i, _posY);
                    } else {
                        _ipc->drawPoint(_posX + i, _posY, _colorOff);
                    }
                }
                x = x << 1;
            }
            break;
        case bddRight:
            for (byte i = 0; i < _arity; i++) {
                if ((_value & x) != 0x00) {
                    if (_paintableObjectOn != nullptr) {
                        _paintableObjectOn->render(_posX - i, _posY);
                    } else {
                        _ipc->drawPoint(_posX - i, _posY, _colorOn);
                    }
                } else {
                    if (_paintableObjectOff != nullptr) {
                        _paintableObjectOff->render(_posX - i, _posY);
                    } else {
                        _ipc->drawPoint(_posX - i, _posY, _colorOff);
                    }
                }
                x = x << 1;
            }
            break;
    }
    _ipc->endUpdate();
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

void NGColorDotMatrixBinaryDigit::registerPaintableObjectOff(NGIPaintableObject *object) {
    _paintableObjectOff = object;
}

void NGColorDotMatrixBinaryDigit::registerPaintableObjectOn(NGIPaintableObject *object) {
    _paintableObjectOn = object;
}
