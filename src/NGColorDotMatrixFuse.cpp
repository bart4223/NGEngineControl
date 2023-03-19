//
//  NGColorDotMatrixFuse.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 15.01.23.
//

#include "NGColorDotMatrixFuse.h"

NGColorDotMatrixFuse::NGColorDotMatrixFuse(NGIPaintableComponent *ipc) {
    _create(ipc, DEFARITY, DEFFUSEDIRECTION, 0, 0);
}

NGColorDotMatrixFuse::NGColorDotMatrixFuse(NGIPaintableComponent *ipc, byte arity) {
    _create(ipc, arity, DEFFUSEDIRECTION, 0, 0);
}

NGColorDotMatrixFuse::NGColorDotMatrixFuse(NGIPaintableComponent *ipc, byte arity, byte posX, byte posY) {
    _create(ipc, arity, DEFFUSEDIRECTION, posX, posY);
}

NGColorDotMatrixFuse::NGColorDotMatrixFuse(NGIPaintableComponent *ipc, byte arity, FuseDirection direction, byte posX, byte posY) {
    _create(ipc, arity, direction, posX, posY);
}

void NGColorDotMatrixFuse::_create(NGIPaintableComponent *ipc, byte arity, FuseDirection direction, byte posX, byte posY) {
    _ipc = ipc;
    _arity = arity;
    _direction = direction;
    _posX = posX;
    _posY = posY;
}

void NGColorDotMatrixFuse::_render() {
    _ipc->beginUpdate();
    switch(_direction) {
        case fdUp:
            for (int i = 0; i < _arity; i++) {
                if (i < _value) {
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
            }
            break;
        case fdDown:
            for (int i = 0; i < _arity; i++) {
                if (i < _value) {
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
            }
            break;
        case fdLeft:
            for (int i = 0; i < _arity; i++) {
                if (i < _value) {
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
            }
            break;
        case fdRight:
            for (int i = 0; i < _arity; i++) {
                if (i < _value) {
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
            }
            break;
    }
    _ipc->endUpdate();
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

void NGColorDotMatrixFuse::registerPaintableObjectOff(NGIPaintableObject *object) {
    _paintableObjectOff = object;
}

void NGColorDotMatrixFuse::registerPaintableObjectOn(NGIPaintableObject *object) {
    _paintableObjectOn = object;
}

