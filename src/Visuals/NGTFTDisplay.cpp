//
//  NGTFTDisplay.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 15.12.25.
//

#include <Visuals/NGTFTDisplay.h>

NGTFTDisplay::NGTFTDisplay() {
    _create(DEFPINTFTCS, DEFPINTFTDC, DEFPINTFTRST);
}

NGTFTDisplay::NGTFTDisplay(byte pinCS, byte pinDC, byte pinRST) {
    _create(pinCS, pinDC, pinRST);
}

void NGTFTDisplay::_create(byte pinCS, byte pinDC, byte pinRST) {
    _TFTScreen = new TFT(pinCS, pinDC, pinRST);
}

int NGTFTDisplay::_convertColor(colorRGB color) {
    return _TFTScreen->Color565(color.blue, color.green, color.red);
}

void NGTFTDisplay::initialize() {
    _TFTScreen->begin();
    clear();
}

void NGTFTDisplay::testSequenceStart() {
    clear();
    setScale(5);
    colorRGB c;
    for (int x = 0; x < getWidth() / getScale(); x++) {
        switch(x) {
            case 0:
                c = COLOR_RED;
                break;
            case 1:
                c = COLOR_GREEN;
                break;
            case 2:
                c = COLOR_BLUE;
                break;
            default:
                c = getRandomColor();
                break;
        }
        drawPoint(x, 0, c);
    }
    setScale(1);
    drawLine(0, 5, getWidth() - 1, getHeight() - 1, COLOR_RED);
    drawRect(15, 10, getHeight() - 11, getWidth() - 11, COLOR_GREEN);
    fillRect(25, 20, getHeight() - 21, getWidth() - 21, COLOR_BLUE);
    drawCircle(getWidth() / 2, getHeight() / 2, min(getWidth(), getHeight()) / 4, COLOR_YELLOW);
    fillCircle(getWidth() / 2, getHeight() / 2, min(getWidth(), getHeight()) / 8, getRandomColor());
}
    
void NGTFTDisplay::testSequenceStop() {
    clear();
}

int NGTFTDisplay::getWidth() {
    return _TFTScreen->width();
}
    
int NGTFTDisplay::getHeight() {
    return _TFTScreen->height();
}
    
void NGTFTDisplay::beginUpdate() {
    if (_updateCount == 0) {
        _TFTScreen->startWrite();
    }
    _updateCount++;
}
    
void NGTFTDisplay::endUpdate() {
    if (_updateCount > 0) {
        _updateCount--;
    }
    if (_updateCount == 0) {
        _TFTScreen->endWrite();
    }
}
    
void NGTFTDisplay::clear() {
    _TFTScreen->fillScreen(_convertColor(_backgroundColor));
}
    
bool NGTFTDisplay::clearPoint(int x, int y) {
    drawPoint(x, y, _backgroundColor);
}
    
bool NGTFTDisplay::drawPoint(int x, int y, colorRGB color) {
    int x_ = (x + _offsetX) * _scale;
    int y_ = (y + _offsetY) * _scale;
    if (_scale > 1) {
        _TFTScreen->fillRect(x_, y_, _scale, _scale, _convertColor(color));
    } else {
        _TFTScreen->drawPixel(x_, y_, _convertColor(color));
    }
}
    
void NGTFTDisplay::clearLine(int x1, int y1, int x2, int y2) {
    drawLine(x1, y1, x2, y2, _backgroundColor);
}
    
void NGTFTDisplay::drawLine(int x1, int y1, int x2, int y2, colorRGB color) {
    int x1_ = (x1 + _offsetX) * _scale;
    int y1_ = (y1 + _offsetY) * _scale;
    int x2_ = (x2 + _offsetX) * _scale;
    int y2_ = (y2 + _offsetY) * _scale;
    int dx =  abs(x2_ - x1_);
    int sx = x1_ < x2_ ? 1 : -1;
    int dy = -abs(y2_ - y1_);
    int sy = y1_ < y2_ ? 1 : -1;
    int err = dx + dy;
    int e2;
    for(;;){
        drawPoint(x1_, y1_, color);
        if (x1_ == x2_ && y1_ == y2_)
            break;
        e2 = 2 * err;
        if (e2 > dy) { err += dy; x1_ += sx; }
        if (e2 < dx) { err += dx; y1_ += sy; }
    }
}
    
void NGTFTDisplay::clearRect(int top, int left, int bottom, int right) {
    drawRect(top, left, bottom, right, _backgroundColor);
}

void NGTFTDisplay::drawRect(int top, int left, int bottom, int right, colorRGB color) {
    beginUpdate();
    drawLine(left, top, right, top, color);
    drawLine(right, top, right, bottom, color);
    drawLine(left, bottom, right, bottom, color);
    drawLine(left, top, left, bottom, color);
    endUpdate();
}

void NGTFTDisplay::fillRect(int top, int left, int bottom, int right, colorRGB color) {
    int left_ = (left + _offsetX) * _scale;
    int top_ = (top + _offsetY) * _scale;
    int right_ = (right + _offsetX) * _scale;
    int bottom_ = (bottom + _offsetY) * _scale;
    _TFTScreen->fillRect(left_, top_, (right_ - left_), (bottom_ - top_), _convertColor(color));
}
    
void NGTFTDisplay::clearCircle(int x0, int y0, int radius) {
    drawCircle(x0, y0, radius, _backgroundColor);
}
    
void NGTFTDisplay::drawCircle(int x0, int y0, int radius, colorRGB color) {
    beginUpdate();
    int x0_ = (x0 + _offsetX) * _scale;
    int y0_ = (y0 + _offsetY) * _scale;
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
    drawPoint(x0_, y0_ + radius, color);
    drawPoint(x0_, y0_ - radius, color);
    drawPoint(x0_ + radius, y0_, color);
    drawPoint(x0_ - radius, y0_, color);
    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x + 1;
        drawPoint(x0_ + x, y0_ + y, color);
        drawPoint(x0_ - x, y0_ + y, color);
        drawPoint(x0_ + x, y0_ - y, color);
        drawPoint(x0_ - x, y0_ - y, color);
        drawPoint(x0_ + y, y0_ + x, color);
        drawPoint(x0_ - y, y0_ + x, color);
        drawPoint(x0_ + y, y0_ - x, color);
        drawPoint(x0_ - y, y0_ - x, color);
    }
    endUpdate();
}    

void NGTFTDisplay::fillCircle(int x0, int y0, int radius, colorRGB color) {
    beginUpdate();
    int x0_ = (x0 + _offsetX) * _scale;
    int y0_ = (y0 + _offsetY) * _scale;
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
    drawLine(x0_ - radius, y0_, x0_ + radius, y0_, color);
    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x + 1;
        drawLine(x0_ - x, y0_ + y, x0_ + x, y0_ + y, color);
        drawLine(x0_ - x, y0_ - y, x0_ + x, y0_ - y, color);
        drawLine(x0_ + y, y0_ + x, x0_ - y, y0_ + x, color);
        drawLine(x0_ + y, y0_ - x, x0_ - y, y0_ - x, color);
    }
    endUpdate();
}
    
void NGTFTDisplay::drawImage(coord2D coord[], colorRGB color, int size) {
    for (int i = 0; i < size; i++) {
        drawPoint(_offsetX + coord[i].x, _offsetY + coord[i].y, color);
    }
}
    
void NGTFTDisplay::drawImage(coord2D coord[], colorRGB color[], int size) {
    for (int i = 0; i < size; i++) {
        drawPoint(_offsetX + coord[i].x, _offsetY + coord[i].y, color[i]);
    }
}
    
void NGTFTDisplay::setScale(int scale) {
    _scale = scale;
}
    
int NGTFTDisplay::getScale() {
    return _scale;
}
    
void NGTFTDisplay::setBackground(colorRGB color) {
    _backgroundColor = color;
}
    
colorRGB NGTFTDisplay::getBackground() {
    return _backgroundColor;
}
    
void NGTFTDisplay::setOffset(int offsetX, int offsetY) {
    _offsetX = offsetX;
    _offsetY = offsetY;
}