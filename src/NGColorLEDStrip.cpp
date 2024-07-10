//
//  NGColorLEDStrip.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 07.07.24.
//

#include "NGColorLEDStrip.h"

NGColorLEDStrip::NGColorLEDStrip(byte pin, int pixelcount) {
    _create(pin, pixelcount, DEFROWCOUNT);
}

NGColorLEDStrip::NGColorLEDStrip(byte pin, int pixelcount, int rowcount) {
    _create(pin, pixelcount, rowcount);
}

void NGColorLEDStrip::_create(byte pin, int pixelcount, int rowcount) {
    _pixelCount = pixelcount;
    _strip = new NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod>(_pixelCount, pin);
    _rowCount = rowcount;
    _colCount = _pixelCount / _rowCount;
}

void NGColorLEDStrip::_render() {
    _strip->Show();
}

void NGColorLEDStrip::initialize() {
    initialize(DEFBRIGHTNESS);
}

void NGColorLEDStrip::initialize(float brightness) {
    _brightness = brightness;
    _strip->Begin();
    clear();
}

void NGColorLEDStrip::setTestColor(colorRGB testcolor) {
    _testColor = testcolor;
    _hasTestColor = true;
}

void NGColorLEDStrip::setOffset(int offsetX, int offsetY) {
    _offsetX = offsetX;
    _offsetY = offsetY;
}

void NGColorLEDStrip::testSequenceStart() {
    beginUpdate();
    for (int y = 0; y < (_rowCount - _offsetY); y++) {
        for (int x = 0; x < (_colCount - _offsetX); x++) {
            if (_hasTestColor) {
                drawPoint(x, y, _testColor);
            } else {
                drawPoint(x, y, getRandomColor());
            }
        }
    }
    endUpdate();
}

void NGColorLEDStrip::testSequenceStop() {
    clear();
}

void NGColorLEDStrip::beginUpdate() {
    _updateCount++;
}

void NGColorLEDStrip::endUpdate() {
    if (_updateCount > 0) {
        _updateCount--;
    }
    render();
}

void NGColorLEDStrip::render() {
    if (_updateCount == 0) {
        _render();
    }
}

int NGColorLEDStrip::getWidth() {
    return _colCount;
}

int NGColorLEDStrip::getHeight() {
    return _rowCount;
}

void NGColorLEDStrip::clear() {
    for (int i = 0; i < _pixelCount; i++) {
        _strip->SetPixelColor(i, RgbColor(_backgroundColor.blue, _backgroundColor.green, _backgroundColor.blue));
    }
    render();
}

bool NGColorLEDStrip::clearPoint(int x, int y) {
    drawPoint(x, y, _backgroundColor);
}

bool NGColorLEDStrip::drawPoint(int x, int y, colorRGB color) {
    int pixel = (y + _offsetY) * _colCount + x + _offsetX;
    if (pixel >= 0 && pixel < _pixelCount) {
        _strip->SetPixelColor(pixel, RgbColor(color.red * _brightness, color.green * _brightness, color.blue * _brightness));
        render();
    }
}

void NGColorLEDStrip::clearLine(int x1, int y1, int x2, int y2) {
    drawLine(x1, y1, x2, y2, _backgroundColor);
}

void NGColorLEDStrip::drawLine(int x1, int y1, int x2, int y2, colorRGB color) {
    int dx =  abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;
    int e2;
    for(;;){
        drawPoint(x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;
        e2 = 2 * err;
        if (e2 > dy) { err += dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}

void NGColorLEDStrip::clearRect(int top, int left, int bottom, int right) {
    drawRect(top, left, bottom, right, _backgroundColor);
}

void NGColorLEDStrip::drawRect(int top, int left, int bottom, int right, colorRGB color) {
    beginUpdate();
    drawLine(top, left, top, right, color);
    drawLine(top, right, bottom, right, color);
    drawLine(bottom, left, bottom, right, color);
    drawLine(top, left, bottom, left, color);
    endUpdate();
}

void NGColorLEDStrip::fillRect(int top, int left, int bottom, int right, colorRGB color) {
    beginUpdate();
    for (int y = top; y <= bottom; y++) {
        drawLine(y, left, y, right, color);
    }
    endUpdate();
}

void NGColorLEDStrip::clearCircle(int x0, int y0, int radius) {
    drawCircle(x0, y0, radius, _backgroundColor);
}

void NGColorLEDStrip::drawCircle(int x0, int y0, int radius, colorRGB color) {
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

void NGColorLEDStrip::drawImage(coord2D coord[], colorRGB color, int size) {
    beginUpdate();
    for (int i = 0; i < size; i++) {
        drawPoint(_offsetX + coord[i].x, _offsetY + coord[i].y, color);
    }
    endUpdate();
}

void NGColorLEDStrip::drawImage(coord2D coord[], colorRGB color[], int size) {
    beginUpdate();
    for (int i = 0; i < size; i++) {
        drawPoint(_offsetX + coord[i].x, _offsetY + coord[i].y, color[i]);
    }
    endUpdate();
}

void NGColorLEDStrip::setScale(int scale) {
    _scale = scale;
}

int NGColorLEDStrip::getScale() {
    return _scale;
}

void NGColorLEDStrip::setBackground(colorRGB color) {
    _backgroundColor = color;
}

colorRGB NGColorLEDStrip::getBackground() {
    return _backgroundColor;
}
