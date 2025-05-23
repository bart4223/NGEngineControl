//
//  NGColorDotMatrix.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 23.10.22.
//

#ifndef NGColorDotMatrix_h
#define NGColorDotMatrix_h

#include <Arduino.h>
#include <rgbMatrix.h>
#include <NGIPaintableComponent.h>

#define DEFCOLORDOTMATRIXSCALE 1
#define DEFCOLORDOTMATRIXBACKGROUND COLOR_BLACK

#define COORDMINTOP     0
#define COORDMINLEFT    0
#define COORDMAXBOTTOM  7
#define COORDMAXRIGHT   7

class NGColorDotMatrix  : public NGIPaintableComponent {
    
private:
    int _updateCount = 0;
    int _scale = DEFCOLORDOTMATRIXSCALE;
    colorRGB _background = DEFCOLORDOTMATRIXBACKGROUND;
    int _offsetX = 0;
    int _offsetY = 0;
    
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
    
    void setBackground(colorRGB color);
    
    colorRGB getBackground();
    
    bool clearPoint(int x, int y);
    
    bool drawPoint(int x, int y, colorRGB color);
    
    void clearLine(int x1, int y1, int x2, int y2);
    
    void drawLine(int x1, int y1, int x2, int y2, colorRGB color);
    
    void drawRect(int top, int left, int bottom, int right, colorRGB color);
    
    void clearRect(int top, int left, int bottom, int right);
    
    void fillRect(int top, int left, int bottom, int right, colorRGB color);
    
    void clearCircle(int x0, int y0, int radius);
    
    void drawCircle(int x0, int y0, int radius, colorRGB color);
    
    void clear();
    
    void drawImage(coord2D coord[], colorRGB color, int size);
    
    void drawImage(coord2D coord[], colorRGB color[], int size);
    
    void setOffset(int offsetX, int offsetY);
};

#endif /* NGColorDotMatrix_h */
