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
#include <Sensors/NGOneWireTemperatureSensor.h>

#define _VERSION "0.8"
#define VERSION (char*)_VERSION

#define MAXEFFECTCOUNT 4
#define DEFTEMPERATUREOBSERVETIME 500
#define NOCURRENTEFFECT -1

class NGOnAirUnitControl : public NGCustomUnitControl {

private:
    NGIEffect *_effects[MAXEFFECTCOUNT];
    NGOneWireTemperatureSensor *_oneWireTemperatureSensor = nullptr;
    int _effectCount = 0;
    int _currentEffectIndex = NOCURRENTEFFECT;
    long _lastTemperatureObserved = 0;
    bool _indicator = false;

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
    
    void registerOneWireTemperatureSensor(NGOneWireTemperatureSensor *sensor);
    
    void initialize();
    
    void processingLoop();
    
    void requestData(byte* data);

    void setCurrentEffect(int effectIndex);
};

#endif /* NGOnAirUnitControl_h */