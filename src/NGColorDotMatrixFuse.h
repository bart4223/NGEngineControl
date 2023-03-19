//
//  NGColorDotMatrixFuse.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 15.01.23.
//

#ifndef NGColorDotMatrixFuse_h
#define NGColorDotMatrixFuse_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGIPaintableObject.h"
#include "NGColorDotMatrix.h"

#define DEFARITY 8
#define DEFFUSEDIRECTION fdLeft

#define FUSE_COLOR_OFF  COLOR_BLACK
#define FUSE_COLOR_ON   COLOR_YELLOW

enum FuseDirection { fdUp, fdDown, fdLeft, fdRight };

class NGColorDotMatrixFuse {
    
private:
    NGIPaintableComponent *_ipc;
    byte _value;
    byte _arity = DEFARITY;
    FuseDirection _direction = DEFFUSEDIRECTION;
    colorRGB _colorOff = FUSE_COLOR_OFF;
    colorRGB _colorOn = FUSE_COLOR_ON;
    byte _posX = 0;
    byte _posY = 0;
    NGIPaintableObject *_paintableObjectOff = nullptr;
    NGIPaintableObject *_paintableObjectOn = nullptr;
    
protected:
    void _create(NGIPaintableComponent *ipc, byte arity, FuseDirection direction, byte posX, byte posY);
    
    void _render();
    
public:
    NGColorDotMatrixFuse(NGIPaintableComponent *ipc);
    
    NGColorDotMatrixFuse(NGIPaintableComponent *ipc, byte arity);
    
    NGColorDotMatrixFuse(NGIPaintableComponent *ipc, byte arity, byte posX, byte posY);
    
    NGColorDotMatrixFuse(NGIPaintableComponent *ipc, byte arity, FuseDirection direction, byte posX, byte posY);
    
    void setColorOff(colorRGB color);
    
    void setColorOn(colorRGB color);
    
    void setValue(byte value);
    
    void registerPaintableObjectOff(NGIPaintableObject *object);

    void registerPaintableObjectOn(NGIPaintableObject *object);
};

#endif /* NGColorDotMatrixFuse_h */
