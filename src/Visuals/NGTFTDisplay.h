//
//  NGTFTDisplay.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 15.12.25.
//

#ifndef NGTFTDisplay_h
#define NGTFTDisplay_h

#include <Arduino.h>
#include <TFT.h> 
#include <SPI.h>
#include <NGITestableComponent.h>
#include <NGIPaintableComponent.h>

#define DEFPINTFTCS    10
#define DEFPINTFTDC     9
#define DEFPINTFTRST    8

class NGTFTDisplay : public NGITestableComponent, public NGIPaintableComponent{

private:
    TFT *_TFTScreen;
    colorRGB _backgroundColor = COLOR_BLACK;
    int _offsetX = 0;
    int _offsetY = 0;
    int _scale = 1;
    
protected:
    void _create(byte pinCS, byte pinDC, byte pinRST);

public:
    NGTFTDisplay();
    
    NGTFTDisplay(byte pinCS, byte pinDC, byte pinRST);
    
    void initialize();

    void testSequenceStart();
    
    void testSequenceStop();

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
    
    void fillCircle(int x0, int y0, int radius, colorRGB color);
    
    void drawImage(coord2D coord[], colorRGB color, int size);
    
    void drawImage(coord2D coord[], colorRGB color[], int size);
    
    void setScale(int scale);
    
    int getScale();
    
    void setBackground(colorRGB color);
    
    colorRGB getBackground();
    
    void setOffset(int offsetX, int offsetY);
};

#endif /* NGTFTDisplay_h */