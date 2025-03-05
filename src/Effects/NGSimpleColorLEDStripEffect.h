//
//  NGSimpleColorLEDStripEffect.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 01.03.25.
//

#ifndef NGSimpleColorLEDStripEffect_h
#define NGSimpleColorLEDStripEffect_h

#include <Arduino.h>
#include <NGIEffect.h>
#include <NGColorLEDStrip.h>

enum simpleLEDStripEffectKind { slsekNone, slsekFlash, slsekAlternate, slsekRunning, slsekRandom };

#define DEFSTEPDELAY 500

class NGSimpleColorLEDStripEffect : public NGIEffect {

private:
    NGColorLEDStrip *_LEDStrip;
    simpleLEDStripEffectKind _kind = slsekNone;
    long _lastStep;
    int _stepDelay = DEFSTEPDELAY;
    byte _currentStep = 0;
    colorRGB _colorOff = COLOR_BLACK;
    colorRGB _colorOn = COLOR_BLACK;

protected:
    void _create(NGColorLEDStrip *LEDStrip, simpleLEDStripEffectKind kind);

    void _render();

public:
    NGSimpleColorLEDStripEffect(NGColorLEDStrip *LEDStrip);
    
    NGSimpleColorLEDStripEffect(NGColorLEDStrip *LEDStrip, simpleLEDStripEffectKind kind);
    
    void setKind(simpleLEDStripEffectKind kind);
    
    void setStepDelay(int stepdelay);

    int getStepDelay();

    void setEffectColors(colorRGB colorOn);

    void setEffectColors(colorRGB colorOn, colorRGB colorOff);
    
    void initialize();

    void processingLoop();
};

#endif /* NGSimpleColorLEDStripEffect_h */