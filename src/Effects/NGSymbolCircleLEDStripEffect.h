//
//  NGSymbolCircleLEDStripEffect.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 26.06.25.
//

#ifndef NGSymbolCircleLEDStripEffect_h
#define NGSymbolCircleLEDStripEffect_h

#include <Arduino.h>
#include <NGIEffect.h>
#include <Visuals/NGCircleLEDStrip.h>

enum symbolCircleLEDStripEffectKind { syclsekNone,syclsekOnAir };

#define DEFSTEPDELAY    500
#define MAXCURRENTSTEPS  10

class NGSymbolCircleLEDStripEffect : public NGIEffect {

private:
    NGCircleLEDStrip *_circleLEDStrip;
    symbolCircleLEDStripEffectKind _kind = syclsekNone;
    long _lastStep;
    int _stepDelay = DEFSTEPDELAY;
    int _currentStep[MAXCURRENTSTEPS];
    byte _currentStepCount = 1;
    colorRGB _colorOne = COLOR_BLACK;
    colorRGB _colorTwo = COLOR_BLACK;

protected:
    void _create(NGCircleLEDStrip *circleLEDStrip, symbolCircleLEDStripEffectKind kind);

    void _render();

    int _getRadius();

public:
    NGSymbolCircleLEDStripEffect(NGCircleLEDStrip *circleLEDStrip);

    NGSymbolCircleLEDStripEffect(NGCircleLEDStrip *circleLEDStrip, symbolCircleLEDStripEffectKind kind);
    
    void initialize();

    void reset();

    void setStepDelay(int stepdelay);

    int getStepDelay();

    void setSymbolColors(colorRGB colorOne, colorRGB colorTwo);

    void processingLoop();
};

#endif /* NGSymbolCircleLEDStripEffect_h */