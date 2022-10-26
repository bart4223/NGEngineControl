//
//  NGColorDotMatrix.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 23.10.22.
//

#include "NGColorDotMatrix.h"

NGColorDotMatrix::NGColorDotMatrix() {
    _create();
}

void NGColorDotMatrix::_create() {
    
}

void NGColorDotMatrix::initialize() {
    RGBMatrixInit();
    clear();
}

void NGColorDotMatrix::render() {
    if (_updateCount == 0) {
        image();
    }
}

void NGColorDotMatrix::beginUpdate() {
    _updateCount++;
}

void NGColorDotMatrix::endUpdate() {
    if (_updateCount > 0) {
        _updateCount--;
    }
    if (_updateCount == 0) {
        render();
    }
}

void NGColorDotMatrix::drawPoint(byte x, byte y, colorRGB color) {
    byte coord[] = {x, y};
    draw_point(coord, color.red, color.green, color.blue);
    render();
}

void NGColorDotMatrix::drawLine(byte x1, byte y1, byte x2, byte y2, colorRGB color) {
    byte coord[] = {x1, y1, x2, y2};
    draw_line(coord, color.red, color.green, color.blue);
    render();
}

void NGColorDotMatrix::drawRect(byte top, byte left, byte bottom, byte right, colorRGB color) {
    beginUpdate();
    byte coord[] = {left, top, right, top};
    draw_line(coord, color.red, color.green, color.blue);
    byte coord2[] = {right, top, right, bottom};
    draw_line(coord2, color.red, color.green, color.blue);
    byte coord3[] = {left, bottom, right, bottom};
    draw_line(coord3, color.red, color.green, color.blue);
    byte coord4[] = {left, top, left, bottom};
    draw_line(coord4, color.red, color.green, color.blue);
    endUpdate();
}

void NGColorDotMatrix::fillRect(byte top, byte left, byte bottom, byte right, colorRGB color) {
    byte coord[] = {top, left, bottom, right};
    draw_rectangle(coord, color.red, color.green, color.blue);
    render();
}

void NGColorDotMatrix::clearRect(byte top, byte left, byte bottom, byte right) {
    fillRect(top, left, bottom, right, COLOR_BLACK);
}

void NGColorDotMatrix::clear() {
    clearRect(COORDMINTOP, COORDMINLEFT, COORDMAXBOTTOM, COORDMAXRIGHT);
}

void NGColorDotMatrix::drawImage(byte coord[][2], colorRGB color, int size) {
    beginUpdate();
    for (int i = 0; i < size; i++) {
        drawPoint(coord[i][0], coord[i][1], color);
    }
    endUpdate();
}

void NGColorDotMatrix::drawImage(byte coord[][2], byte color[][3], int size) {
    beginUpdate();
    for (int i = 0; i < size; i++) {
        drawPoint(coord[i][0], coord[i][1], { color[i][0], color[i][1], color[i][2] });
    }
    endUpdate();
}
