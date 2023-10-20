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

#define _VERSION "0.1"
#define VERSION (char*)_VERSION

#define MAXLIGHTINGAREACOUNT 3

struct candleArchLightingAreaStruct
{
    NG8BitShiftRegister *switcher;
};
typedef struct candleArchLightingAreaStruct candleArchLightingArea;

class NGCandleArchUnitControl : public NGCustomUnitControl, NGITestableComponent {
    
private:
    candleArchLightingArea _lightingAreas[MAXLIGHTINGAREACOUNT];
    byte _lightingAreaCount = 0;
    
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
    
    void initialize();
    
    void processingLoop();
    
    void requestData(byte* data);
    
    void testSequenceStart();
    
    void testSequenceStop();
};

#endif /* NGCandleArchUnitControl_h */
