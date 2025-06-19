//
//  NGCircleLEDStrip.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 19.06.25.
//

#include <Visuals/NGCircleLEDStrip.h>

NGCircleLEDStrip::NGCircleLEDStrip(byte pin, int pixelcount) {
    _create(pin, pixelcount, DEFRADIUSCOUNT, NOPINAUTODETECTION);
}

NGCircleLEDStrip::NGCircleLEDStrip(byte pin, int pixelcount, int radiuscount) {
    _create(pin, pixelcount, radiuscount, NOPINAUTODETECTION);
}

void NGCircleLEDStrip::_create(byte pin, int pixelcount, int radiuscount, int pinautodetection) {
    NGColorLEDStrip::_create(pin, pixelcount, 1, lskCircle, pinautodetection);
    _radiusCount = radiuscount;
    for (int i = 0; i < _radiusCount; i++) {
        _radius[i].startpixel = 0;
    }
}

void NGCircleLEDStrip::registerRadius(int radius, int startpixel) {
    if (radius > 0 && radius <= _radiusCount) {
        _radius[radius - 1].startpixel = startpixel;
    }
}

void NGCircleLEDStrip::testSequenceStart() {
    beginUpdate();
    clear();
    switch(_testMode) {
        case tmDefault:
            for (int i = 0; i <= _radiusCount; i++) {
                if (_hasTestColor) {
                    drawCircle(0, 0, i, _testColor);
                } else {
                    drawCircle(0, 0, i, getRandomColor());
                }
                if (_testModeDelay > 0) {
                    _strip->Show();
                    delay(_testModeDelay);
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
    
void NGCircleLEDStrip::drawCircle(int x0, int y0, int radius, colorRGB color) {
    beginUpdate();
    if (radius > 0 && radius <= _radiusCount) {
        int start = _radius[radius - 1].startpixel;
        int end = _pixelCount - 1;
        if (radius < _radiusCount) {
            end = _radius[radius].startpixel - 1;
        }
        for (int i = start; i <= end; i++) {
            _strip->SetPixelColor(i, RgbColor(color.red * _brightness, color.green * _brightness, color.blue * _brightness));
        }
    }
    endUpdate();
}