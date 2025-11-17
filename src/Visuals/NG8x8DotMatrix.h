//
//  NG8x8DotMatrix.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 19.04.25.
//

#ifndef NG8x8DotMatrix_h
#define NG8x8DotMatrix_h

#include <Arduino.h>
#include <LedControl.h>
#include <NGITestableComponent.h>
#include <NGIPaintableComponent.h>

#define DEFPINCS  10
#define DEFPINCLK 11
#define DEFPINDIN 12

#define DEFMAX7219COUNT    1
#define DEFMAX7219ROWCOUNT 8
#define DEFMAX7219COLCOUNT 8

#define DEFCOLOR     COLOR_RED
#define DEFBACKCOLOR COLOR_BLACK

#define DEFBRIGHTNESS    1.00
#define DEFMINBRIGHTNESS 0.01
#define DEFMAXBRIGHTNESS 1.00

#define DEFTESTMODEDELAY  50

enum dotmatrixAddressingMode { dmamNormal, dmamInverse };
enum dotmatrixRenderMode { dmrNormal, dmrMirroredX, dmrMirroredY, dmrMirroredXY };

#define DEFADDRESSINGMODE dmamNormal
#define DEFRENDERMODE     dmrNormal

class NG8x8DotMatrix : public NGITestableComponent, public NGIPaintableComponent {

private:
    LedControl *_lc;
    int _rowCount;
    int _colCount;
    float _brightness = 0.0;
    int _offsetX = 0;
    int _offsetY = 0;
    int _scale = 1;
    int _testModeDelay = DEFTESTMODEDELAY;
    dotmatrixAddressingMode _adressingMode = DEFADDRESSINGMODE;
    dotmatrixRenderMode _renderMode = DEFRENDERMODE;
    float _maxBrightness = DEFMAXBRIGHTNESS;
    float _minBrightness = DEFMINBRIGHTNESS;
    bool _changeBrightnessUp = true;
    bool _logging = false;

protected:
    void _create(byte pinCS, byte pinCLK, byte pinDIN, byte count, byte rowcount, byte colcount, dotmatrixAddressingMode adressingmode, dotmatrixRenderMode rendermode);

    void _renderLED(int x, int y, bool ledOn);

public:
    NG8x8DotMatrix();
    
    NG8x8DotMatrix(byte count, byte rowcount, byte colcount);

    NG8x8DotMatrix(byte count, byte rowcount, byte colcount, dotmatrixAddressingMode adressingmode);
    
    NG8x8DotMatrix(byte count, byte rowcount, byte colcount, dotmatrixAddressingMode adressingmode, dotmatrixRenderMode rendermode);
    
    NG8x8DotMatrix(byte pinCS, byte pinCLK, byte pinDIN, byte count, byte rowcount, byte colcount);
    
    void initialize();

    void initialize(float brightness);

    void testSequenceStart();
    
    void testSequenceStop();

    void setLogging(bool logging);

    int getWidth();
    
    int getHeight();
    
    void beginUpdate();
    
    void endUpdate();
    
    void clear();
    
    bool clearPoint(int x, int y);
    
    bool drawPoint(int x, int y, colorRGB color);
    
    void clearLine(int x1, int y1, int x2, int y2);
    
    void drawLine(int x1, int y1, int x2, int y2, colorRGB color);
    
    void drawRect(int top, int left, int bottom, int right, colorRGB color);
    
    void clearRect(int top, int left, int bottom, int right);
    
    void fillRect(int top, int left, int bottom, int right, colorRGB color);
    
    void clearCircle(int x0, int y0, int radius);
    
    void drawCircle(int x0, int y0, int radius, colorRGB color);
    
    void drawImage(coord2D coord[], colorRGB color, int size);
    
    void drawImage(coord2D coord[], colorRGB color[], int size);
    
    void setScale(int scale);
    
    int getScale();
    
    void setBackground(colorRGB color);
    
    colorRGB getBackground();
    
    void setOffset(int offsetX, int offsetY);

    void setBrightness(float brightness);
    
    float getBrightness();
    
    bool isMinBrightness();
    
    bool isMaxBrightness();
    
    void incrementBrightness();
    
    void decrementBrightness();
    
    void changeBrightness();
};

#endif /* NG8x8DotMatrix_h */