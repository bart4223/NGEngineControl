//
//  NGCandleArchUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 20.10.23.
//

#ifndef NGCandleArchUnitControl_h
#define NGCandleArchUnitControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomUnitControl.h>
#include <NGITestableComponent.h>
#include <NG8BitShiftRegister.h>

#define _VERSION "0.4"
#define VERSION (char*)_VERSION

#define MAXLIGHTINGAREACOUNT 3
#define MAXLIGHTSCOUNT 8

struct candleArchLightingAreaStruct
{
    NG8BitShiftRegister *switcher;
    byte lights[MAXLIGHTSCOUNT];
    byte lightscount = 0;
};
typedef struct candleArchLightingAreaStruct candleArchLightingArea;

class NGCandleArchUnitControl : public NGCustomUnitControl, NGITestableComponent {
    
private:
    candleArchLightingArea _lightingAreas[MAXLIGHTINGAREACOUNT];
    byte _lightingAreaCount = 0;
    byte _lastLightSensorId = 0x00;
    bool _processLightSensorId = false;
    
protected:
    void _create(char* name, byte address, int serialRate);
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
    void _processingIRRemoteData();
    
public:
    NGCandleArchUnitControl();

    NGCandleArchUnitControl(char* name);
                  
    NGCandleArchUnitControl(char* name, byte address);
    
    NGCandleArchUnitControl(char* name, byte address, int serialRate);

    byte registerLightingArea(byte switcherLatchPin, byte switcherClockPin, byte switcherDataPin);
    
    byte registerLight(byte area);
    
    void initialize();
    
    void processingLoop();
        
    void requestData(byte* data);
    
    void testSequenceStart();
    
    void testSequenceStop();
    
    void switchLight(byte area, byte light, bool on);
    
    bool isLightOn(byte area, byte light);

    void toogleLight(byte area, byte light);
    
    void setLightSensorData(byte id);
};

#endif /* NGCandleArchUnitControl_h */
