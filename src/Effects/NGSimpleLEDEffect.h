//
//  NGSimpleLEDEffect.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 16.01.25.
//

#ifndef NGSimpleLEDEffect_h
#define NGSimpleLEDEffect_h

#include <Arduino.h>
#include <NGIEffect.h>
#include <NGSimpleLED.h>

struct simpleLEDEffectStruct
{
    NGSimpleLED *LED;
};
typedef struct simpleLEDEffectStruct simpleLEDEffect;

enum simpleLEDEffectKind { slekAlternate };

#define MAXSIMPLELEDEFFECTCOUNT 3
#define DEFSTEPDELAY 500

class NGSimpleLEDEffect : NGIEffect {

private:
    simpleLEDEffect _simpleLEDs[MAXSIMPLELEDEFFECTCOUNT];
    byte _simpleLEDCount = 0;
    bool _effectOn = false;
    simpleLEDEffectKind _kind = slekAlternate;
    byte _currentStep = 0;
    long _lastStep = 0;
    int _stepDelay = DEFSTEPDELAY;

protected:
    void _create();

    void _render();

public:
    NGSimpleLEDEffect();

    byte registerLED(NGSimpleLED *led);

    void setStepDelay(int stepdelay);
    
    void initialize();

    void processingLoop();

    void effectOn();

    void effectOff();
};

#endif /* NGSimpleLEDEffect_h */