//
//  NGTFTDisplay.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 15.12.25.
//

#ifndef NGTFTDisplay_h
#define NGTFTDisplay_h

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <NGITestableComponent.h>
#include <NGIPaintableComponent.h>

#define DEFPINTFTCS    10
#define DEFPINTFTDC     9
#define DEFPINTFTRST    8

#define DEFTFTDISPLAYDIRECTION tddHorizontal
#define DEFTFTSPIRATE 15000000

enum TFTDisplayDirection { tddHorizontal, tddVertical };

class NGTFTDisplay : public NGITestableComponent, public NGIPaintableComponent{

private:
    Adafruit_ST7735 *_TFTScreen;
    colorRGB _backgroundColor = COLOR_BLACK;
    int _offsetX = 0;
    int _offsetY = 0;
    int _scale = 1;
    int _updateCount = 0;
    TFTDisplayDirection _direction = DEFTFTDISPLAYDIRECTION;
    
protected:
    void _create(byte pinCS, byte pinDC, byte pinRST, TFTDisplayDirection direction, long SPIRate);
    void _initDisplayDirection();
    int _convertColor(colorRGB color);

public:
    NGTFTDisplay();
    
    NGTFTDisplay(byte pinCS, byte pinDC, byte pinRST);

    NGTFTDisplay(byte pinCS, byte pinDC, byte pinRST, long SPIRate);
    
    void initialize();

    void testSequenceStart();
    
    void testSequenceStop();

    void setDisplayDirection(TFTDisplayDirection direction);

    TFTDisplayDirection getDisplayDirection();

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