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

int NGColorDotMatrix::getWidth() {
    return COORDMAXRIGHT + 1;
}

int NGColorDotMatrix::getHeight() {
    return COORDMAXBOTTOM + 1;
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

void NGColorDotMatrix::setBackColor(colorRGB color) {
    set_backcolor(color.red, color.green, color.blue);
}

void NGColorDotMatrix::setGamma(int gamma) {
    gamma32(gamma);
}

void NGColorDotMatrix::setColorHSV(int hue, int sat, int val) {
    ColorHSV(hue, sat, val);
}

void NGColorDotMatrix::setScale(int scale) {
    _scale = 1;
}

int NGColorDotMatrix::getScale() {
    return _scale;
}

void NGColorDotMatrix::setBackground(colorRGB color) {
    _background = color;
}

colorRGB NGColorDotMatrix::getBackground() {
    return _background;
}

bool NGColorDotMatrix::clearPoint(int x, int y) {
    return drawPoint(x, y, _background);
}

bool NGColorDotMatrix::drawPoint(int x, int y, colorRGB color) {
    bool res = x >= 0 && x < 8 && y >= 0 && y < 8;
    if (res) {
        byte coord[] = {x, y};
        draw_point(coord, color.red, color.green, color.blue);
        render();
    }
    return res;
}

void NGColorDotMatrix::clearLine(int x1, int y1, int x2, int y2) {
    drawLine(x1, y1, x2, y2, _background);
}

void NGColorDotMatrix::drawLine(int x1, int y1, int x2, int y2, colorRGB color) {
    byte coord[] = {x1, y1, x2, y2};
    draw_line(coord, color.red, color.green, color.blue);
    render();
}

void NGColorDotMatrix::drawRect(int top, int left, int bottom, int right, colorRGB color) {
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

void NGColorDotMatrix::fillRect(int top, int left, int bottom, int right, colorRGB color) {
    byte coord[] = {top, left, bottom, right};
    draw_rectangle(coord, color.red, color.green, color.blue);
    render();
}

void NGColorDotMatrix::clearRect(int top, int left, int bottom, int right) {
    fillRect(top, left, bottom, right, _background);
}

void NGColorDotMatrix::clearCircle(int x0, int y0, int radius) {
    drawCircle(x0, y0, radius, _background);
}

void NGColorDotMatrix::drawCircle(int x0, int y0, int radius, colorRGB color) {
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
    drawPoint(x0, y0 + radius, color);
    drawPoint(x0, y0 - radius, color);
    drawPoint(x0 + radius, y0, color);
    drawPoint(x0 - radius, y0, color);
    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x + 1;
        drawPoint(x0 + x, y0 + y, color);
        drawPoint(x0 - x, y0 + y, color);
        drawPoint(x0 + x, y0 - y, color);
        drawPoint(x0 - x, y0 - y, color);
        drawPoint(x0 + y, y0 + x, color);
        drawPoint(x0 - y, y0 + x, color);
        drawPoint(x0 + y, y0 - x, color);
        drawPoint(x0 - y, y0 - x, color);
    }
}

void NGColorDotMatrix::clear() {
    clearRect(COORDMINTOP, COORDMINLEFT, COORDMAXBOTTOM, COORDMAXRIGHT);
}

void NGColorDotMatrix::drawImage(coord2D coord[], colorRGB color, int size) {
    beginUpdate();
    for (int i = 0; i < size; i++) {
        drawPoint(_offsetX + coord[i].x, _offsetY + coord[i].y, color);
    }
    endUpdate();
}

void NGColorDotMatrix::drawImage(coord2D coord[], colorRGB color[], int size) {
    beginUpdate();
    for (int i = 0; i < size; i++) {
        drawPoint(_offsetX + coord[i].x, _offsetY + coord[i].y, color[i]);
    }
    endUpdate();
}

void NGColorDotMatrix::setOffset(int offsetX, int offsetY) {
    _offsetX = offsetX;
    _offsetY = offsetY;
}
