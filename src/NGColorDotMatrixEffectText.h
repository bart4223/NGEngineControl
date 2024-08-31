//
//  NGColorDotMatrixEffectText.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 31.08.24.
//

#ifndef NGColorDotMatrixEffectText_h
#define NGColorDotMatrixEffectText_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGCommonGraphics.h"
#include "NGIEffect.h"
#include "NGCustomFont.h"
#include "NGIPaintableComponent.h"
#include "NGColorDotMatrixCharDigit.h"

#define DEFNEXTCHARDELAY 500

class NGColorDotMatrixEffectText: public NGIEffect {
    
private:
    NGColorDotMatrixCharDigit *_charDigit;
    int _posX = 0;
    int _posY = 0;
    char *_text;
    int _currentPos = 0;
    long _lastStep = 0;
    int _delay = DEFNEXTCHARDELAY;
    
protected:
    void _create(NGIPaintableComponent *ipc, colorRGB color, colorRGB colorBackground, NGCustomFont *font);
    
public:
    NGColorDotMatrixEffectText(NGIPaintableComponent *ipc);
    
    NGColorDotMatrixEffectText(NGIPaintableComponent *ipc, NGCustomFont *font);
    
    NGColorDotMatrixEffectText(NGIPaintableComponent *ipc, colorRGB color, NGCustomFont *font);

    NGColorDotMatrixEffectText(NGIPaintableComponent *ipc, colorRGB color, colorRGB colorBackground, NGCustomFont *font);

    void initialize();
    
    void setPosition(int posx, int posy);
    
    void setDelay(int delay);

    void setText(char *text);    
    
    void processingLoop();
};

#endif /* NGColorDotMatrixEffectText_h */
