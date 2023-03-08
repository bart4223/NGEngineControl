//
//  NGColorDotMatrixDecimalDigit.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 02.03.23.
//

#ifndef NGColorDotMatrixDecimalDigit_h
#define NGColorDotMatrixDecimalDigit_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGColorDotMatrix.h"

class NGColorDotMatrixDecimalDigit {
    
private:
    int _updateCount = 0;
    NGIPaintableComponent *_ipc;
    byte _value;
    bool _randomColorBackground = false;
    colorRGB _colorBackground = COLOR_BLACK;
    bool _randomColor = false;
    colorRGB _color = COLOR_GREEN;
    int _posX = 0;
    int _posY = 0;
    
protected:
    void _create(NGIPaintableComponent *ipc, byte posX, byte posY);
    
    void _render();
    
    byte _getNumeralZero(byte line);
    
    byte _getNumeralOne(byte line);
    
    byte _getNumeralTwo(byte line);
    
    byte _getNumeralThree(byte line);
    
    byte _getNumeralFour(byte line);
    
    byte _getNumeralFive(byte line);
    
    byte _getNumeralSix(byte line);
    
    byte _getNumeralSeven(byte line);
    
    byte _getNumeralEight(byte line);
    
    byte _getNumeralNine(byte line);
    
public:
    static const int PIXELCOUNT = 8;
    
    NGColorDotMatrixDecimalDigit(NGIPaintableComponent *ipc);
    
    void beginUpdate();
    
    void endUpdate();
    
    void setRandomColorBackground(bool randomcolor);
    
    void setColorBackground(colorRGB color);
    
    void setRandomColor(bool randomcolor);
    
    void setColor(colorRGB color);
    
    void setValue(byte value);
    
    void setPosX(int x);
    
    int getPosX();
    
    void setPosY(int y);
    
    int getPosY();
    
    int getScale();
};

#endif /* NGColorDotMatrixDecimalDigit_h */
