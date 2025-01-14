//
//  NGColorDotMatrixCustomDigit.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 21.04.24.
//

#ifndef NGColorDotMatrixCustomDigit_h
#define NGColorDotMatrixCustomDigit_h

#include <Arduino.h>
#include <NGCustomFont.h>
#include <NGIPaintableComponent.h>

class NGColorDotMatrixCustomDigit {
    
private:
    int _updateCount = 0;
    NGIPaintableComponent *_ipc;
    bool _randomColorBackground = false;
    colorRGB _colorBackground = COLOR_BLACK;
    bool _randomColor = false;
    colorRGB _color = COLOR_GREEN;
    int _posX = 0;
    int _posY = 0;
    NGCustomFont *_font = nullptr;
    
protected:
    char _value;
    
    void _create(NGIPaintableComponent *ipc, byte posX, byte posY);
    
    void _render();
    
    NGCustomFont* _getFont();
    
public:
    static const int PIXELCOUNT = 8;
    
    NGIPaintableComponent* getPaintableComponent();
    
    void beginUpdate();
    
    void endUpdate();
    
    void setRandomColorBackground(bool randomcolor);
    
    void setColorBackground(colorRGB color);
    
    colorRGB getColorBackground();
    
    void setRandomColor(bool randomcolor);
    
    void setColor(colorRGB color);
    
    colorRGB getColor();
    
    void setFont(NGCustomFont *font);
    
    NGCustomFont* getFont();
    
    void setChar(char value);
    
    void setPosX(int x);
    
    int getPosX();
    
    void setPosY(int y);
    
    int getPosY();
    
    int getScale();
};

#endif /* NGColorDotMatrixCustomDigit_h */
