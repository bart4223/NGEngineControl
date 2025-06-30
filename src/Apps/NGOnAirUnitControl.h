//
//  NGOnAirUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.06.25.
//

#ifndef NGOnAirUnitControl_h
#define NGOnAirUnitControl_h

#include <Arduino.h>
#include <NGCustomUnitControl.h>
#include <NGIEffect.h>

#define _VERSION "0.7"
#define VERSION (char*)_VERSION

#define MAXEFFECTCOUNT 4

class NGOnAirUnitControl : public NGCustomUnitControl {

private:
    NGIEffect *_effects[MAXEFFECTCOUNT];
    int _effectCount = 0;
    int _currentEffectIndex = -1;

protected:
    void _create(char* name, byte address, int serialRate);
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
    void _processingIRRemoteData();

public:
    NGOnAirUnitControl();
    
    NGOnAirUnitControl(char* name);
                  
    NGOnAirUnitControl(char* name, byte address);
    
    NGOnAirUnitControl(char* name, byte address, int serialRate);

    byte registerEffect(NGIEffect *effect);    
    
    void initialize();
    
    void processingLoop();
    
    void requestData(byte* data);

    void setCurrentEffect(int effectIndex);
};

#endif /* NGOnAirUnitControl_h */