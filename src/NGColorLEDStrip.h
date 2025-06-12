//
//  NGColorLEDStrip.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 07.07.24.
//

#ifndef NGColorLEDStrip_h
#define NGColorLEDStrip_h

#include <Arduino.h>
#include <NeoPixelBus.h>
#include <NGCommonGraphics.h>
#include <NGITestableComponent.h>
#include <NGIPaintableComponent.h>

#define DEFROWCOUNT      1
#define DEFBRIGHTNESS    1
#define DEFPIXELCOUNT    1

#define DEFTESTMODEDELAY 100
#define DEFLEDSTRIPKIND lskLeftRightStrict

#define NOPINAUTODETECTION -1
#define DEFINDICATORRANGE  21

#define MAXGEOMETRYCOUNT 3

#define DEFMINBRIGHTNESS 0.01
#define DEFMAXBRIGHTNESS 1.00

enum testMode {tmDefault, tmPixel};
enum LEDStripKind {lskLeftRightStrict, lskLeftRightAlternate, lskUpDownStrict, lskUpDownAlternate, lskCircle};

struct colorLEDStripGeometryStruct
{
    int indicatorvalue;
    LEDStripKind kind;
    int pixelcount;
    int rowcount;
};
typedef struct colorLEDStripGeometryStruct colorLEDStripGeometry;

class NGColorLEDStrip : public NGITestableComponent, public NGIPaintableComponent {
    
private:
    NeoPixelBus<NeoGrbFeature, NeoWs2812xMethod> *_strip;
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
    float _brightness = 0.0;
    testMode _testMode = tmDefault;
    int _testModeDelay = DEFTESTMODEDELAY;
    LEDStripKind _stripKind = DEFLEDSTRIPKIND;
    byte _pin;
    int _pinAutoDetection = NOPINAUTODETECTION;
    colorLEDStripGeometry _geometry[MAXGEOMETRYCOUNT];
    byte _geometryCount = 0;
    bool _logging = false;
    int _indicatorRange = DEFINDICATORRANGE;
    float _maxBrightness = DEFMAXBRIGHTNESS;
    float _minBrightness = DEFMINBRIGHTNESS;
    bool _changeBrightnessUp = true;
    
protected:
    void _create(byte pin, int pixelcount, int rowcount, LEDStripKind stripkind, int pinautodetection);
    void _render();
    void _determineGeometry(int indicatorvalue);
    
public:
    NGColorLEDStrip(byte pin, byte pinautodetection);
    
    NGColorLEDStrip(byte pin, int pixelcount);
    
    NGColorLEDStrip(byte pin, int pixelcount, LEDStripKind stripkind);
    
    NGColorLEDStrip(byte pin, int pixelcount, int rowcount);
    
    NGColorLEDStrip(byte pin, int pixelcount, int rowcount, LEDStripKind stripkind);
    
    void initialize();
    
    void initialize(float brightness);
    
    void registerGeometry(int geometryindicatorvalue, int pixelcount, int rowcount);
    
    void registerGeometry(int geometryindicatorvalue, LEDStripKind kind, int pixelcount, int rowcount);
    
    void setLogging(bool logging);
    
    void setIndicatorRange(int indicatorrange);
    
    void setTestColor(colorRGB testcolor);
    
    void setTestMode(testMode testmode);
    
    void setTestModeDelay(int testmodedelay);
    
    void setOffset(int offsetX, int offsetY);
    
    void setBrightness(float brightness);
    
    float getBrightness();
    
    bool isMinBrightness();
    
    bool isMaxBrightness();
    
    void incrementBrightness();
    
    void decrementBrightness();
    
    void changeBrightness();

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
