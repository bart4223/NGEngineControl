//
//  NGColorDotMatrixEffectText.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 31.08.24.
//

#ifndef NGColorDotMatrixEffectText_h
#define NGColorDotMatrixEffectText_h

#include <Arduino.h>
#include <NGCommonGraphics.h>
#include <NGIEffect.h>
#include <Fonts/NGCustomFont.h>
#include <NGIPaintableComponent.h>
#include <NGColorDotMatrixCharDigit.h>

enum simpleEffectTextKind { setkSingle, setkFull };

#define DEFNEXTCHARDELAY 500
#define DEFSIMPLEEFFECTKIND setkSingle

class NGColorDotMatrixEffectText: public NGIEffect {
    
private:
    NGColorDotMatrixCharDigit *_charDigit;
    int _posX = 0;
    int _posY = 0;
    char *_text;
    int _currentPos = 0;
    long _lastStep = 0;
    int _delay = DEFNEXTCHARDELAY;
    simpleEffectTextKind _kind = DEFSIMPLEEFFECTKIND;
    
protected:
    void _create(NGIPaintableComponent *ipc, colorRGB color, colorRGB colorBackground, NGCustomFont *font, simpleEffectTextKind kind);
    
    void _renderEffectKindSingle();

    void _renderEffectKindFull();

public:
    NGColorDotMatrixEffectText(NGIPaintableComponent *ipc);
    
    NGColorDotMatrixEffectText(NGIPaintableComponent *ipc, NGCustomFont *font);
    
    NGColorDotMatrixEffectText(NGIPaintableComponent *ipc, colorRGB color, NGCustomFont *font);

    NGColorDotMatrixEffectText(NGIPaintableComponent *ipc, colorRGB color, NGCustomFont *font, simpleEffectTextKind kind);

    NGColorDotMatrixEffectText(NGIPaintableComponent *ipc, colorRGB color, colorRGB colorBackground, NGCustomFont *font);

    void initialize();
    
    void setPosition(int posx, int posy);
    
    void setDelay(int delay);

    void setText(char *text);    
    
    void processingLoop();
};

#endif /* NGColorDotMatrixEffectText_h */
