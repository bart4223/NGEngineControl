//
//  NG8x8DotMatrix.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 19.04.25.
//

#include <Visuals/NG8x8DotMatrix.h>

NG8x8DotMatrix::NG8x8DotMatrix() {
    _create(DEFPINCS, DEFPINCLK, DEFPINDIN, DEFMAX7219COUNT, DEFMAX7219ROWCOUNT, DEFMAX7219COLCOUNT, DEFADDRESSINGMODE);
}

NG8x8DotMatrix::NG8x8DotMatrix(byte count, byte rowcount, byte colcount) {
    _create(DEFPINCS, DEFPINCLK, DEFPINDIN, count, rowcount, colcount, DEFADDRESSINGMODE);
}

NG8x8DotMatrix::NG8x8DotMatrix(byte count, byte rowcount, byte colcount, dotmatrixAddressingMode adressingmode) {
    _create(DEFPINCS, DEFPINCLK, DEFPINDIN, count, rowcount, colcount, adressingmode);
}

NG8x8DotMatrix::NG8x8DotMatrix(byte pinCS, byte pinCLK, byte pinDIN, byte count, byte rowcount, byte colcount) {
    _create(pinCS, pinCLK, pinDIN, count, rowcount, colcount, DEFADDRESSINGMODE);
}

void NG8x8DotMatrix::_create(byte pinCS, byte pinCLK, byte pinDIN, byte count, byte rowcount, byte colcount, dotmatrixAddressingMode adressingmode) {
    _lc = new LedControl(pinDIN, pinCLK, pinCS, count);
    _rowCount = rowcount;
    _colCount = colcount;
    _adressingMode = adressingmode; 
}

void NG8x8DotMatrix::_renderLED(int x, int y, bool ledOn) {
    int xx = x + _offsetX;
    int yy = y + _offsetY;
    if (xx >= 0 && xx < _colCount && yy >= 0 && yy < _rowCount) {
        byte addr = (xx / DEFMAX7219COLCOUNT + 1) * (yy / DEFMAX7219ROWCOUNT + 1) - 1;
        switch(_adressingMode) {
            case dmamInverse:
                addr = _lc->getDeviceCount() - addr - 1;
                break;
        }
        _lc->setLed(addr, yy % DEFMAX7219ROWCOUNT, xx % DEFMAX7219COLCOUNT, ledOn);
    }
}

void NG8x8DotMatrix::initialize() {
    float brightness = _brightness;
    if (brightness == 0.0) {
        brightness = DEFBRIGHTNESS;
    }
    initialize(brightness);
}

void NG8x8DotMatrix::initialize(float brightness) {
    _brightness = brightness;
    for (int i = 0; i < _lc->getDeviceCount(); i++) {
        _lc->shutdown(i, false);
        _lc->setIntensity(i, _brightness * 15);
    }
    clear();
}

void NG8x8DotMatrix::testSequenceStart() {
    clear();
    for (int y = 0; y < _rowCount; y++) {
        for (int x = 0; x < _colCount; x++) {
            drawPoint(x, y, DEFCOLOR);
            delay(_testModeDelay);
        }
    }  
}
    
void NG8x8DotMatrix::testSequenceStop() {
    clear();
}

int NG8x8DotMatrix::getWidth() {
    return _colCount;
}
    
int NG8x8DotMatrix::getHeight() {
    return _rowCount;
}
    
void NG8x8DotMatrix::beginUpdate() {
    // Nop
}

void NG8x8DotMatrix::endUpdate() {
    // Nop
}

void NG8x8DotMatrix::clear() {
    for (int i = 0; i < _lc->getDeviceCount(); i++) {
        _lc->clearDisplay(i);
    }
}

bool NG8x8DotMatrix::clearPoint(int x, int y) {
    _renderLED(x, y, false);
}

bool NG8x8DotMatrix::drawPoint(int x, int y, colorRGB color) {
    _renderLED(x, y, !isSameColor(color, DEFBACKCOLOR));
}

void NG8x8DotMatrix::clearLine(int x1, int y1, int x2, int y2) {
    drawLine(x1, y1, x2, y2, DEFBACKCOLOR);
}

void NG8x8DotMatrix::drawLine(int x1, int y1, int x2, int y2, colorRGB color) {
    beginUpdate();
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
    endUpdate();
}

void NG8x8DotMatrix::drawRect(int top, int left, int bottom, int right, colorRGB color) {
    beginUpdate();
    drawLine(top, left, top, right, color);
    drawLine(top, right, bottom, right, color);
    drawLine(bottom, left, bottom, right, color);
    drawLine(top, left, bottom, left, color);
    endUpdate();
}

void NG8x8DotMatrix::clearRect(int top, int left, int bottom, int right) {
    drawRect(top, left, bottom, right, DEFBACKCOLOR);
}

void NG8x8DotMatrix::fillRect(int top, int left, int bottom, int right, colorRGB color) {
    beginUpdate();
    for (int y = top; y <= bottom; y++) {
        drawLine(y, left, y, right, color);
    }
    endUpdate();
}

void NG8x8DotMatrix::clearCircle(int x0, int y0, int radius) {
    drawCircle(x0, y0, radius, DEFBACKCOLOR);
}

void NG8x8DotMatrix::drawCircle(int x0, int y0, int radius, colorRGB color) {
    beginUpdate();
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
    endUpdate();
}

void NG8x8DotMatrix::drawImage(coord2D coord[], colorRGB color, int size) {
    beginUpdate();
    for (int i = 0; i < size; i++) {
        drawPoint(_offsetX + coord[i].x, _offsetY + coord[i].y, color);
    }
    endUpdate();
}

void NG8x8DotMatrix::drawImage(coord2D coord[], colorRGB color[], int size) {
    beginUpdate();
    for (int i = 0; i < size; i++) {
        drawPoint(_offsetX + coord[i].x, _offsetY + coord[i].y, color[i]);
    }
    endUpdate();
}

void NG8x8DotMatrix::setScale(int scale) {
    _scale = scale;
}

int NG8x8DotMatrix::getScale() {
    return _scale;
}

void NG8x8DotMatrix::setBackground(colorRGB color) {
    // Nop
}

colorRGB NG8x8DotMatrix::getBackground() {
    return COLOR_BLACK;
}

void NG8x8DotMatrix::setOffset(int offsetX, int offsetY) {
    _offsetX = offsetX;
    _offsetY = offsetY;
}