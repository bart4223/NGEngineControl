//
//  NGColorDotMatrixText.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 23.04.24.
//

#ifndef NGColorDotMatrixText_h
#define NGColorDotMatrixText_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGColorDotMatrixCharDigit.h"

class NGColorDotMatrixText {
    
private:
    NGColorDotMatrixCharDigit *_digit;
    byte _posX = 0x00;
    byte _posY = 0x00;
    bool _wrapText = false;
    
protected:
    void _create(NGIPaintableComponent *ipc);
    
public:
    NGColorDotMatrixText(NGIPaintableComponent *ipc);
    
    void setFont(NGCustomFont *font);
    
    NGCustomFont* getFont();
    
    void setColorBackground(colorRGB color);
    
    colorRGB getColorBackground();
    
    void setColor(colorRGB color);
    
    colorRGB getColor();
    
    void setText(char* text);
    
    void setWrapText(bool wraptext);
    
    bool getWrapText();
    
    void setPosX(byte posx);
    
    void setPosY(byte posy);
};

#endif /* NGColorDotMatrixText_h */
