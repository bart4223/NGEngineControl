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

#include "NGIPaintableObject.h"
#include "NGColorDotMatrix.h"

enum BinaryDigitDirection { bddUp, bddDown, bddLeft, bddRight };

#define DEFARITY 4
#define DEFBINARYDIGITDIRECTION bddUp

#define BD_COLOR_OFF { .red = 2, .green = 2, .blue = 2 }
#define BD_COLOR_ON COLOR_WHITE

class NGColorDotMatrixBinaryDigit {
    
private:
    NGIPaintableComponent *_ipc;
    byte _value;
    byte _arity = DEFARITY;
    BinaryDigitDirection _direction = DEFBINARYDIGITDIRECTION;
    colorRGB _colorOff = BD_COLOR_OFF;
    colorRGB _colorOn = BD_COLOR_ON;
    byte _posX = 0;
    byte _posY = 0;
    NGIPaintableObject *_paintableObjectOff = nullptr;
    NGIPaintableObject *_paintableObjectOn = nullptr;

protected:
    void _create(NGIPaintableComponent *ipc, byte arity, BinaryDigitDirection direction, byte posX, byte posY);
    
    void _render();
    
public:
    NGColorDotMatrixBinaryDigit(NGIPaintableComponent *ipc);
    
    NGColorDotMatrixBinaryDigit(NGIPaintableComponent *ipc, byte posX, byte posY);
    
    NGColorDotMatrixBinaryDigit(NGIPaintableComponent *ipc, byte arity, byte posX, byte posY);
    
    NGColorDotMatrixBinaryDigit(NGIPaintableComponent *ipc, byte arity);
    
    NGColorDotMatrixBinaryDigit(NGIPaintableComponent *ipc, byte arity, BinaryDigitDirection direction);
    
    NGColorDotMatrixBinaryDigit(NGIPaintableComponent *ipc, byte arity, BinaryDigitDirection direction, byte posX, byte posY);
    
    void setColorOff(colorRGB color);

    void setColorOn(colorRGB color);

    void setValue(byte value);
    
    void registerPaintableObjectOff(NGIPaintableObject *object);

    void registerPaintableObjectOn(NGIPaintableObject *object);
};

#endif /* NGColorDotMatrixBinaryDigit_h */
