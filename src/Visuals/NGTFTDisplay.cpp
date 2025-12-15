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
    // n/a
}
    
void NGTFTDisplay::endUpdate() {
    // n/a
}
    
void NGTFTDisplay::clear() {
    _TFTScreen->background(0, 0, 0);
}
    
bool NGTFTDisplay::clearPoint(int x, int y) {
    drawPoint(x, y, _backgroundColor);
}
    
bool NGTFTDisplay::drawPoint(int x, int y, colorRGB color) {
    int x0 = x + _offsetX;
    int y0 = y + _offsetY;
    _TFTScreen->stroke(color.blue, color.green, color.red);
    if (_scale > 1) {
        _TFTScreen->fill(color.blue, color.green, color.red);
        _TFTScreen->rect(x0 * _scale, y0 * _scale, _scale, _scale);
    } else {
        _TFTScreen->point(x0, y0);
    }
}
    
void NGTFTDisplay::clearLine(int x1, int y1, int x2, int y2) {
    drawLine(x1, y1, x2, y2, _backgroundColor);
}
    
void NGTFTDisplay::drawLine(int x1, int y1, int x2, int y2, colorRGB color) {
    int x1_ = x1 + _offsetX;
    int y1_ = y1 + _offsetY;
    int x2_ = x2 + _offsetX;
    int y2_ = y2 + _offsetY;
    _TFTScreen->stroke(color.blue, color.green, color.red);
    _TFTScreen->line(x1_ * _scale,  y1_ * _scale, x2_ * _scale, y2_ * _scale);
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
    int left_ = left + _offsetX;
    int top_ = top + _offsetY;
    int right_ = right + _offsetX;
    int bottom_ = bottom + _offsetY;
    _TFTScreen->stroke(color.blue, color.green, color.red);
    _TFTScreen->fill(color.blue, color.green, color.red);
    _TFTScreen->rect(left_ * _scale, top_ * _scale, (right_ - left_) * _scale, (bottom_ - top_) * _scale);
}
    
void NGTFTDisplay::clearCircle(int x0, int y0, int radius) {
    drawCircle(x0, y0, radius, _backgroundColor);
}
    
void NGTFTDisplay::drawCircle(int x0, int y0, int radius, colorRGB color) {
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

void NGTFTDisplay::fillCircle(int x0, int y0, int radius, colorRGB color) {
    int x0_ = x0 + _offsetX;
    int y0_ = y0 + _offsetY;
    _TFTScreen->stroke(color.blue, color.green, color.red);
    _TFTScreen->fill(color.blue, color.green, color.red);
    _TFTScreen->circle(x0_ * _scale, y0_ * _scale, radius * _scale);
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
    _TFTScreen->background(_backgroundColor.red, _backgroundColor.green, _backgroundColor.blue);
}
    
colorRGB NGTFTDisplay::getBackground() {
    return _backgroundColor;
}
    
void NGTFTDisplay::setOffset(int offsetX, int offsetY) {
    _offsetX = offsetX;
    _offsetY = offsetY;
}