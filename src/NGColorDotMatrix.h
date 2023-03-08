//
//  NGColorDotMatrix.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 23.10.22.
//

#ifndef NGColorDotMatrix_h
#define NGColorDotMatrix_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <rgbMatrix.h>
#include <NGIPaintableComponent.h>

#define COORDMINTOP     0
#define COORDMINLEFT    0
#define COORDMAXBOTTOM  7
#define COORDMAXRIGHT   7

class NGColorDotMatrix  : public NGIPaintableComponent {
    
private:
    int _updateCount = 0;
    
protected:
    void _create();
    
public:
    NGColorDotMatrix();
    
    void initialize();
    
    void render();
    
    int getWidth();
    
    int getHeight();
    
    void beginUpdate();
    
    void endUpdate();
    
    void setBackColor(colorRGB color);
    
    void setGamma(int gamma);
    
    void setColorHSV(int hue, int sat, int val);
    
    void setScale(int scale);
    
    int getScale();
    
    bool clearPoint(byte x, byte y);
    
    bool drawPoint(int x, int y, colorRGB color);
    
    void clearLine(byte x1, byte y1, byte x2, byte y2);
    
    void drawLine(byte x1, byte y1, byte x2, byte y2, colorRGB color);
    
    void drawRect(byte top, byte left, byte bottom, byte right, colorRGB color);
    
    void clearRect(byte top, byte left, byte bottom, byte right);
    
    void fillRect(byte top, byte left, byte bottom, byte right, colorRGB color);
    
    void clearCircle(byte x0, byte y0, byte radius);
    
    void drawCircle(byte x0, byte y0, byte radius, colorRGB color);
    
    void clear();
    
    void drawImage(byte coord[][2], colorRGB color, int size);

    void drawImage(byte coord[][2], byte color[][3], int size);
};

#endif /* NGColorDotMatrix_h */
