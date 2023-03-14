//
//  NGIPaintableComponent.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 03.03.23.
//

#ifndef NGIPaintableComponent_h
#define NGIPaintableComponent_h

#include <NGCommonGraphics.h>

class NGIPaintableComponent {
    
public:
    virtual int getWidth();
    
    virtual int getHeight();
    
    virtual void beginUpdate();
    
    virtual void endUpdate();
    
    virtual void clear();
    
    virtual bool clearPoint(int x, int y);
    
    virtual bool drawPoint(int x, int y, colorRGB color);
    
    virtual void clearLine(int x1, int y1, int x2, int y2);
    
    virtual void drawLine(int x1, int y1, int x2, int y2, colorRGB color);
    
    virtual void drawRect(int top, int left, int bottom, int right, colorRGB color);
    
    virtual void clearRect(int top, int left, int bottom, int right);
    
    virtual void fillRect(int top, int left, int bottom, int right, colorRGB color);
    
    virtual void clearCircle(int x0, int y0, int radius);
    
    virtual void drawCircle(int x0, int y0, int radius, colorRGB color);
    
    virtual void drawImage(coord2D coord[], colorRGB color, int size);
    
    virtual void drawImage(int offsetX, int offsetY, coord2D coord[], colorRGB color, int size);
    
    virtual void drawImage(coord2D coord[], colorRGB color[], int size);
    
    virtual void drawImage(int offsetX, int offsetY, coord2D coord[], colorRGB color[], int size);
    
    virtual void setScale(int scale);
    
    virtual int getScale();
    
    virtual void setBackground(colorRGB color);
    
    virtual colorRGB getBackground();
};

#endif /* NGIPaintableComponent_h */
