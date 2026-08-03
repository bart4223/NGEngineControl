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

#define _VERSION "1.3"
#define VERSION (char*)_VERSION

#define MAXEFFECTCOUNT 10
#define NOCURRENTEFFECT -1
#define NOHOTEFFECT -1
#define MAXCOLORCOUNT 10
#define NOCURRENTCOLOR -1

struct glassesEffectItemStruct
{    
    glassesEffectKind kind = glekNone;
    int delay = 0;
};
typedef struct glassesEffectItemStruct glassesEffectItem;

class NGiGlassesUnitControl : public NGCustomUnitControl {

private:
    NGIGlassesEffect *_effectImplementation = nullptr;
    glassesEffectItem _effects[MAXEFFECTCOUNT];
    int _effectCount = 0;
    int _currentEffectIndex = NOCURRENTEFFECT;
    bool _effectRunning = false;
    int _hotEffectIndex = NOHOTEFFECT;
    colorRGB _colors[MAXCOLORCOUNT];
    int _colorCount = 0;
    int _currentColorIndex = NOCURRENTCOLOR;
    
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

    void setEffectImplementation(NGIGlassesEffect *effect);

    bool hasEffectImplementation();

    byte registerEffect(glassesEffectKind kind);

    byte registerEffect(glassesEffectKind kind, int delay);

    byte registerEffect(glassesEffectKind kind, bool hotEffect);

    byte registerEffect(glassesEffectKind kind, bool hotEffect, int delay);
    
    byte registerColor(colorRGB color);

    void initialize();
    
    void processingLoop();
    
    void requestData(byte* data);

    bool hasEffects();

    void setCurrentEffect(int effectIndex);

    int getCurrentEffect();

    bool hasCurrentEffect();

    void firstEffect();

    void nextEffect();

    void hotEffect();

    bool hasHotEffect();

    bool hasColors();

    void setCurrentColor(int colorIndex);

    int getCurrentColor();

    bool hasCurrentColor();

    void firstColor();

    void nextColor();

    void startEffectRunning();

    void stopEffectRunning();

    void toggleEffectRunning();

    bool isEffectRunning();
};

#endif /* NGiGlassesUnitControl_h */