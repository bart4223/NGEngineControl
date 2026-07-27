//
//  NGiGlassesUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 10.07.26.
//

#ifndef NGiGlassesUnitControl_h
#define NGiGlassesUnitControl_h

#include <Arduino.h>
#include <NGCustomUnitControl.h>
#include <Effects/NGIGlassesEffect.h>

#define _VERSION "0.5"
#define VERSION (char*)_VERSION

#define MAXEFFECTCOUNT 10
#define NOCURRENTEFFECT -1
#define NOHOTEFFECT -1

struct glassesEffectItemStruct
{    
    NGIGlassesEffect *effect;
    glassesEffectKind kind = glekNone;
};
typedef struct glassesEffectItemStruct glassesEffectItem;

class NGiGlassesUnitControl : public NGCustomUnitControl {

private:
    glassesEffectItem _effects[MAXEFFECTCOUNT];
    int _effectCount = 0;
    int _currentEffectIndex = NOCURRENTEFFECT;
    bool _effectRunning = false;
    int _hotEffectIndex = NOHOTEFFECT;

protected:
    void _create(char* name, byte address, int serialRate);
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
    void _processingIRRemoteData();

    void _observeTemperature();

public:
    NGiGlassesUnitControl();
    
    NGiGlassesUnitControl(char* name);
                  
    NGiGlassesUnitControl(char* name, byte address);
    
    NGiGlassesUnitControl(char* name, byte address, int serialRate);

    byte registerEffect(NGIGlassesEffect *effect, glassesEffectKind kind);

    byte registerEffect(NGIGlassesEffect *effect, glassesEffectKind kind, bool hotEffect);
    
    bool hasEffects();

    void initialize();
    
    void processingLoop();
    
    void requestData(byte* data);

    void setCurrentEffect(int effectIndex);

    int getCurrentEffect();

    void firstEffect();

    void nextEffect();

    void hotEffect();

    bool hasHotEffect();

    bool hasCurrentEffect();

    void startEffectRunning();

    void stopEffectRunning();

    void toggleEffectRunning();

    bool isEffectRunning();
};

#endif /* NGiGlassesUnitControl_h */