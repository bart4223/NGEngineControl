//
//  NGColorDotMatrixBinaryDigit.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.10.22.
//

#ifndef NGColorDotMatrixBinaryDigit_h
#define NGColorDotMatrixBinaryDigit_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGColorDotMatrix.h"

enum BinaryDigitDirection { bddUp, bddDown, bddLeft, bddRight };

#define DEFARITY 4
#define DEFBINARYDIGITDIRECTION bddUp

#define BD_COLOR_OFF { .red = 2, .green = 2, .blue = 2 }
#define BD_COLOR_ON COLOR_WHITE

class NGColorDotMatrixBinaryDigit {
    
private:
    NGColorDotMatrix *_cdm;
    byte _value;
    byte _arity = DEFARITY;
    BinaryDigitDirection _direction = DEFBINARYDIGITDIRECTION;
    colorRGB _colorOff = BD_COLOR_OFF;
    colorRGB _colorOn = BD_COLOR_ON;
    byte _posX = 0;
    byte _posY = 0;

protected:
    void _create(NGColorDotMatrix *cdm, byte arity, BinaryDigitDirection direction, byte posX, byte posY);
    
    void _render();
    
public:
    NGColorDotMatrixBinaryDigit(NGColorDotMatrix *cdm);
    
    NGColorDotMatrixBinaryDigit(NGColorDotMatrix *cdm, byte posX, byte posY);
    
    NGColorDotMatrixBinaryDigit(NGColorDotMatrix *cdm, byte arity, byte posX, byte posY);
    
    NGColorDotMatrixBinaryDigit(NGColorDotMatrix *cdm, byte arity);
    
    NGColorDotMatrixBinaryDigit(NGColorDotMatrix *cdm, byte arity, BinaryDigitDirection direction);
    
    NGColorDotMatrixBinaryDigit(NGColorDotMatrix *cdm, byte arity, BinaryDigitDirection direction, byte posX, byte posY);
    
    void setColorOff(colorRGB color);

    void setColorOn(colorRGB color);

    void setValue(byte value);
};

#endif /* NGColorDotMatrixBinaryDigit_h */
