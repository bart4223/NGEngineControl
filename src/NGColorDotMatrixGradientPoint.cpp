//
//  NGColorDotMatrixGradientPoint.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 01.05.24.
//

#include "NGColorDotMatrixGradientPoint.h"

NGColorDotMatrixGradientPoint::NGColorDotMatrixGradientPoint(NGIPaintableComponent *ipc, colorRGB color) {
    _create(ipc, color, DEFGRADIENTSTAGES, false);
}

NGColorDotMatrixGradientPoint::NGColorDotMatrixGradientPoint(NGIPaintableComponent *ipc, colorRGB color, int gradientStages) {
    _create(ipc, color, gradientStages, false);
}

NGColorDotMatrixGradientPoint::NGColorDotMatrixGradientPoint(NGIPaintableComponent *ipc, colorRGB color, int gradientStages, bool randomPosition) {
    _create(ipc, color, gradientStages, randomPosition);
}

void NGColorDotMatrixGradientPoint::_create(NGIPaintableComponent *ipc, colorRGB color, int gradientStages, bool randomPosition) {
    _ipc = ipc;
    _dc = new NGDimmableColor(color);
    _gradientStages = gradientStages;
    if (randomPosition) {
        _x = random(0, _ipc->getWidth());
        _y = random(0, _ipc->getHeight());
    }
}

void NGColorDotMatrixGradientPoint::_render() {
    int offsetX = 0;
    int offsetY = 0;
    int damping = 0;
    int dampingX = 0;
    int dampingY = 0;
    if (_gradientX != 0) {
        dampingX = _dc->getMaxDamping() - map(abs(_gradientX), 0, _gradientStages, 0, _dc->getDampingRange()) * -1;
        offsetX = 1;
        if (_gradientX < 0) {
            offsetX = -1;
        }
    }
    if (_gradientY != 0) {
        dampingY = _dc->getMaxDamping() - map(abs(_gradientY), 0, _gradientStages, 0, _dc->getDampingRange()) * -1;
        offsetY = 1;
        if (_gradientY < 0) {
            offsetY = -1;
        }
    }
    if (dampingX != 0 && dampingY != 0) {
        damping = (dampingX + dampingY) / 2;
    } else if (dampingX != 0) {
        damping = dampingX;
    } else if (dampingY != 0) {
        damping = dampingY;
    }
    if (offsetX != 0 || offsetY != 0) {
        _ipc->drawPoint(_x + offsetX, _y + offsetY, _dc->setDamping(damping));
    }
    if (damping != 0) {
        damping = _dc->getMaxDamping() - damping;
    }
    _ipc->drawPoint(_x, _y, _dc->setDamping(damping));
}

void NGColorDotMatrixGradientPoint::_clear() {
    int offsetX = 0;
    int offsetY = 0;
    if (_gradientX != 0) {
        offsetX = 1;
        if (_gradientX < 0) {
            offsetX = -1;
        }
    }
    if (_gradientY != 0) {
        offsetY = 1;
        if (_gradientY < 0) {
            offsetY = -1;
        }
    }
    _ipc->clearPoint(_x + offsetX, _y + offsetY);
    _ipc->clearPoint(_x, _y);
}

void NGColorDotMatrixGradientPoint::refresh() {
    _ipc->beginUpdate();
    _render();
    _ipc->endUpdate();
}

void NGColorDotMatrixGradientPoint::clear() {
    if (_updateCount == 0) {
        _ipc->beginUpdate();
        _clear();
        _ipc->endUpdate();
    }
}

byte NGColorDotMatrixGradientPoint::getGradientStages() {
    return _gradientStages;
}

void NGColorDotMatrixGradientPoint::setPosition(int x, int y) {
    _x = x;
    _y = y;
    if (_updateCount == 0) {
        refresh();
    }
}

int NGColorDotMatrixGradientPoint::getPositionX() {
    return _x;
}

int NGColorDotMatrixGradientPoint::getPositionY() {
    return _y;
}

void NGColorDotMatrixGradientPoint::setGradient(int gradientX, int gradientY) {
    _gradientX = gradientX;
    _gradientY = gradientY;
    if (_updateCount == 0) {
        refresh();
    }
}

int NGColorDotMatrixGradientPoint::getGradientX() {
    return _gradientY;
}

int NGColorDotMatrixGradientPoint::getGradientY() {
    return _gradientX;
}

void NGColorDotMatrixGradientPoint::beginUpdate() {
    _updateCount++;
}

void NGColorDotMatrixGradientPoint::endUpdate(){
    if (_updateCount > 0) {
        _updateCount--;
        if (_updateCount == 0) {
            refresh();
        }
    }
}
