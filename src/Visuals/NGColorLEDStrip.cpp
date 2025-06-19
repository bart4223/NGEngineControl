//
//  NGColorLEDStrip.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 07.07.24.
//

#include "NGColorLEDStrip.h"

NGColorLEDStrip::NGColorLEDStrip() {
    _create(DEFLEDSTRIPPIN, DEFPIXELCOUNT, DEFROWCOUNT, DEFLEDSTRIPKIND, NOPINAUTODETECTION);
}

NGColorLEDStrip::NGColorLEDStrip(byte pin, byte pinautodetection) {
    _create(pin, DEFPIXELCOUNT, DEFROWCOUNT, DEFLEDSTRIPKIND, pinautodetection);
}

NGColorLEDStrip::NGColorLEDStrip(byte pin, int pixelcount) {
    _create(pin, pixelcount, DEFROWCOUNT, DEFLEDSTRIPKIND, NOPINAUTODETECTION);
}

NGColorLEDStrip::NGColorLEDStrip(byte pin, int pixelcount, LEDStripKind stripkind) {
    _create(pin, pixelcount, DEFROWCOUNT, stripkind, NOPINAUTODETECTION);
}

NGColorLEDStrip::NGColorLEDStrip(byte pin, int pixelcount, int rowcount) {
    _create(pin, pixelcount, rowcount, DEFLEDSTRIPKIND, NOPINAUTODETECTION);
}

NGColorLEDStrip::NGColorLEDStrip(byte pin, int pixelcount, int rowcount, LEDStripKind stripkind) {
    _create(pin, pixelcount, rowcount, stripkind, NOPINAUTODETECTION);
}

void NGColorLEDStrip::_create(byte pin, int pixelcount, int rowcount, LEDStripKind stripkind, int pinautodetection) {
    _pin = pin;
    _pinAutoDetection = pinautodetection;
    _stripKind = stripkind;
    _pixelCount = pixelcount;
    _rowCount = rowcount;
}

void NGColorLEDStrip::_render() {
    _strip->Show();
}

void NGColorLEDStrip::_determineGeometry(int indicatorvalue) {
    if (_logging) {
        char log[100];
        sprintf(log, "i: %d", indicatorvalue);
        Serial.println(log);
    }
    for (int i = 0; i < _geometryCount; i++) {
        if ((indicatorvalue - _indicatorRange) <= _geometry[i].indicatorvalue && _geometry[i].indicatorvalue <= (indicatorvalue + _indicatorRange)) {
            _stripKind = _geometry[i].kind;
            _pixelCount = _geometry[i].pixelcount;
            _rowCount = _geometry[i].rowcount;
            return;
        }
    }
}

void NGColorLEDStrip::initialize() {
    float brightness = _brightness;
    if (brightness == 0.0) {
        brightness = DEFBRIGHTNESS;
    }
    initialize(brightness);
}

void NGColorLEDStrip::initialize(float brightness) {
    _brightness = brightness;
    if (_pinAutoDetection != NOPINAUTODETECTION) {
        _determineGeometry(analogRead(_pinAutoDetection));
    }
    _strip = new NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod>(_pixelCount, _pin);
    _strip->Begin();
    _colCount = _pixelCount / _rowCount;
    clear();
}

void NGColorLEDStrip::registerGeometry(int geometryindicatorvalue, int pixelcount, int rowcount) {
    registerGeometry(geometryindicatorvalue, DEFLEDSTRIPKIND, pixelcount, rowcount);
}

void NGColorLEDStrip::registerGeometry(int geometryindicatorvalue, LEDStripKind kind, int pixelcount, int rowcount) {
    colorLEDStripGeometry geometry;
    geometry.indicatorvalue = geometryindicatorvalue;
    geometry.kind = kind;
    geometry.pixelcount = pixelcount;
    geometry.rowcount = rowcount;
    _geometry[_geometryCount] = geometry;
    _geometryCount++;
}

void NGColorLEDStrip::setLogging(bool logging) {
    _logging = logging;
}

void NGColorLEDStrip::setIndicatorRange(int indicatorrange) {
    _indicatorRange = indicatorrange;
}

void NGColorLEDStrip::setTestColor(colorRGB testcolor) {
    _testColor = testcolor;
    _hasTestColor = true;
}

void NGColorLEDStrip::setTestMode(testMode testmode) {
    _testMode = testmode;
}

void NGColorLEDStrip::setTestModeDelay(int testmodedelay) {
    _testModeDelay = testmodedelay;
}

void NGColorLEDStrip::setOffset(int offsetX, int offsetY) {
    _offsetX = offsetX;
    _offsetY = offsetY;
}

void NGColorLEDStrip::setBrightness(float brightness) {
    _brightness = brightness;
    if (_logging) {
        Serial.print("b: ");
        Serial.println(_brightness);
    }
}

float NGColorLEDStrip::getBrightness() {
    return _brightness;
}

bool NGColorLEDStrip::isMinBrightness() {
    return getBrightness() == _minBrightness;
}

bool NGColorLEDStrip::isMaxBrightness() {
    return getBrightness() == _maxBrightness;
}

void NGColorLEDStrip::incrementBrightness() {
    float brightness = getBrightness();
    float step = 0.1;
    if (brightness <= 0.09) {
        step = 0.01;
    }
    brightness = brightness + step;
    if (brightness > _maxBrightness) {
        brightness = _maxBrightness;
    }
    setBrightness(brightness);
}

void NGColorLEDStrip::decrementBrightness() {
    float brightness = getBrightness();
    float step = 0.1;
    if (brightness <= 0.1) {
        step = 0.01;
    }
    brightness = brightness - step;
    if (brightness < _minBrightness) {
        brightness = _minBrightness;
    }
    setBrightness(brightness);
}

void NGColorLEDStrip::changeBrightness() {
    if (_changeBrightnessUp) {
        if (getBrightness() < _maxBrightness) {
            incrementBrightness();
        } else {
            _changeBrightnessUp = false;
            decrementBrightness();
        }
    } else {
        if (getBrightness() > _minBrightness) {
            decrementBrightness();
        } else {
            _changeBrightnessUp = true;
            incrementBrightness();
        }
    }
}

void NGColorLEDStrip::testSequenceStart() {
    beginUpdate();
    clear();
    switch(_testMode) {
        case tmDefault:
            for (int y = 0; y < (_rowCount - _offsetY); y++) {
                for (int x = 0; x < (_colCount - _offsetX); x++) {
                    if (_hasTestColor) {
                        drawPoint(x, y, _testColor);
                    } else {
                        drawPoint(x, y, getRandomColor());
                    }
                    if (_testModeDelay > 0) {
                        _strip->Show();
                        delay(_testModeDelay);
                    }
                }
            }
            break;
        case tmPixel:
            for (int i = 0; i < _pixelCount; i++) {
                colorRGB c = _testColor;
                if (!_hasTestColor) {
                    c = getRandomColor();
                }
                _strip->SetPixelColor(i, RgbColor(c.red * _brightness, c.green * _brightness, c.blue * _brightness));
                if (_testModeDelay > 0) {
                    _strip->Show();
                    delay(_testModeDelay);
                }
            }
            break;
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
        _strip->SetPixelColor(i, RgbColor(_backgroundColor.red * _brightness, _backgroundColor.green * _brightness, _backgroundColor.blue * _brightness));
    }
    render();
}

bool NGColorLEDStrip::clearPoint(int x, int y) {
    drawPoint(x, y, _backgroundColor);
}

bool NGColorLEDStrip::drawPoint(int x, int y, colorRGB color) {
    int x0 = x + _offsetX;
    int y0 = y + _offsetY;
    bool res = x0 >= 0 && x0 < getWidth() && y0 >= 0 && y0 < getHeight();
    if (res) {
        int pixel = -1;
        switch(_stripKind) {
            case lskLeftRightStrict:
                pixel = y0 * _colCount + x0;
                break;
            case lskUpDownAlternate:
                if (x0 % 2 == 1)
                  y0 = _colCount - y0 - 1;
                pixel = x0 * _rowCount + y0;
                break;
        }
        if (pixel >= 0 && pixel < _pixelCount) {
            _strip->SetPixelColor(pixel, RgbColor(color.red * _brightness, color.green * _brightness, color.blue * _brightness));
            render();
        }
    }
    return res;
}

void NGColorLEDStrip::clearLine(int x1, int y1, int x2, int y2) {
    drawLine(x1, y1, x2, y2, _backgroundColor);
}

void NGColorLEDStrip::drawLine(int x1, int y1, int x2, int y2, colorRGB color) {
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
