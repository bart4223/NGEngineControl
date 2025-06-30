//
//  NGSimpleCircleLEDStripEffect.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 23.06.25.
//

#ifndef NGSimpleCircleLEDStripEffect_h
#define NGSimpleCircleLEDStripEffect_h

#include <Arduino.h>
#include <NGIEffect.h>
#include <Visuals/NGCircleLEDStrip.h>

enum simpleCircleLEDStripEffectKind { sclsekNone, sclsekPulse };

#define DEFSTEPDELAY    500
#define MAXCURRENTSTEPS  10

class NGSimpleCircleLEDStripEffect : public NGIEffect {

private:
    NGCircleLEDStrip *_circleLEDStrip;
    simpleCircleLEDStripEffectKind _kind = sclsekNone;
    long _lastStep;
    int _stepDelay = DEFSTEPDELAY;
    int _currentStep[MAXCURRENTSTEPS];
    byte _currentStepCount = 1;
    colorRGB _colorOff = COLOR_BLACK;
    colorRGB _colorOn = COLOR_BLACK;

protected:
    void _create(NGCircleLEDStrip *circleLEDStrip, simpleCircleLEDStripEffectKind kind);

    void _render();

    void _clear();

    int _getRadius();

public:
    NGSimpleCircleLEDStripEffect(NGCircleLEDStrip *circleLEDStrip);

    NGSimpleCircleLEDStripEffect(NGCircleLEDStrip *circleLEDStrip, simpleCircleLEDStripEffectKind kind);
    
    void initialize();

    void reset();

    void setStepDelay(int stepdelay);

    int getStepDelay();

    void setEffectColors(colorRGB colorOn);

    void setEffectColors(colorRGB colorOn, colorRGB colorOff);

    void processingLoop();
};

#endif /* NGSimpleCircleLEDStripEffect_h */