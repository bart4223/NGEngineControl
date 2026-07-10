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
#include <NGIEffect.h>

#define _VERSION "0.1"
#define VERSION (char*)_VERSION

#define MAXEFFECTCOUNT 4
#define DEFTEMPERATUREOBSERVETIME 500
#define NOCURRENTEFFECT -1

class NGiGlassesUnitControl : public NGCustomUnitControl {

private:
    NGIEffect *_effects[MAXEFFECTCOUNT];
    int _effectCount = 0;
    int _currentEffectIndex = NOCURRENTEFFECT;

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

    byte registerEffect(NGIEffect *effect);
    
    void initialize();
    
    void processingLoop();
    
    void requestData(byte* data);

    void setCurrentEffect(int effectIndex);

    int getCurrentEffect();
};

#endif /* NGiGlassesUnitControl_h */