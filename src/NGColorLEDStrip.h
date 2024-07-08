//
//  NGColorLEDStrip.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 07.07.24.
//

#ifndef NGColorLEDStrip_h
#define NGColorLEDStrip_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "Adafruit_NeoPixel.h"
#include "NGCommonGraphics.h"
#include "NGITestableComponent.h"
#include "NGIPaintableComponent.h"

#define DEFROWCOUNT      1
#define DEFBRIGHTNESS 0xFF

class NGColorLEDStrip : public NGITestableComponent, NGIPaintableComponent {
    
private:
    Adafruit_NeoPixel *_neoPixel;
    int _pixelCount;
    int _rowCount;
    int _colCount;
    int _updateCount = 0;
    int _offsetX = 0;
    int _offsetY = 0;
    bool _hasTestColor = false;
    colorRGB _testColor;
    colorRGB _backgroundColor = COLOR_BLACK;
    int _scale = 1;
    
protected:
    void _create(byte pin, int pixelcount, int rowcount);
    void _render();
    
public:
    NGColorLEDStrip(byte pin, int pixelcount);
    
    NGColorLEDStrip(byte pin, int pixelcount, int rowcount);
    
    void initialize();
    
    void initialize(byte brightness);
    
    void setTestColor(colorRGB testcolor);
    
    void setOffset(int offsetX, int offsetY);

    void testSequenceStart();

    void testSequenceStop();
    
    void beginUpdate();
    
    void endUpdate();

    void render();
    
    int getWidth();
    
    int getHeight();

    void clear();
    
    bool clearPoint(int x, int y);

    bool drawPoint(int x, int y, colorRGB color);
    
    void clearLine(int x1, int y1, int x2, int y2);
    
    void drawLine(int x1, int y1, int x2, int y2, colorRGB color);
    
    void clearRect(int top, int left, int bottom, int right);
    
    void drawRect(int top, int left, int bottom, int right, colorRGB color);
    
    void fillRect(int top, int left, int bottom, int right, colorRGB color);
    
    void clearCircle(int x0, int y0, int radius);
    
    void drawCircle(int x0, int y0, int radius, colorRGB color);
    
    void drawImage(coord2D coord[], colorRGB color, int size);
    
    void drawImage(coord2D coord[], colorRGB color[], int size);
    
    void setScale(int scale);
    
    int getScale();
    
    void setBackground(colorRGB color);
    
    colorRGB getBackground();
};

#endif /* NGColorLEDStrip_h */
