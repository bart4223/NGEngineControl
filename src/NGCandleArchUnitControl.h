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

#define _VERSION "0.7"
#define VERSION (char*)_VERSION

#define MAXLIGHTINGAREACOUNT 3
#define MAXLIGHTSCOUNT 8

#define MAXSCENARIOCOUNT  4
#define NOACTIVESCENARIO -1

struct candleArchLightingAreaStruct
{
    NG8BitShiftRegister *switcher;
    byte lights[MAXLIGHTSCOUNT];
    byte lightscount = 0;
};
typedef struct candleArchLightingAreaStruct candleArchLightingArea;

struct candleArchLightingScenarioAreaStruct
{
    byte area;
    byte lights[MAXLIGHTSCOUNT];
    byte lightscount = 0;
};
typedef struct candleArchLightingScenarioAreaStruct candleArchLightingScenarioArea;

enum candleArchLightingScenarioKind { calskNone, calskLightSensor };

struct candleArchLightingScenarioStruct
{
    candleArchLightingScenarioKind kind;
    byte thresholdid;
    candleArchLightingScenarioArea areas[MAXLIGHTINGAREACOUNT];
    byte areacount = 0;
};
typedef struct candleArchLightingScenarioStruct candleArchLightingScenario;

class NGCandleArchUnitControl : public NGCustomUnitControl, NGITestableComponent {
    
private:
    candleArchLightingScenario _lightingScenarios[MAXSCENARIOCOUNT];
    byte _lightingScenarioCount = 0;
    candleArchLightingArea _lightingAreas[MAXLIGHTINGAREACOUNT];
    byte _lightingAreaCount = 0;
    byte _lastLightSensorThresholdId = 0x00;
    bool _processLightSensorThresholdId = false;
    int _activeScenario = NOACTIVESCENARIO;
    
protected:
    void _create(char* name, byte address, int serialRate);
    
    byte _registerScenario(candleArchLightingScenarioKind kind, byte thresholdid);
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
    void _processingIRRemoteData();
    
    void _beginAllAreaUpdate();
    
    void _endAllAreaUpdate();

public:
    NGCandleArchUnitControl();

    NGCandleArchUnitControl(char* name);
                  
    NGCandleArchUnitControl(char* name, byte address);
    
    NGCandleArchUnitControl(char* name, byte address, int serialRate);

    byte registerLightingArea(byte switcherLatchPin, byte switcherClockPin, byte switcherDataPin);
    
    byte registerLight(byte area);
    
    byte registerScenario();
    
    byte registerLightSensorScenario(byte thresholdid);
    
    byte registerScenarioArea(byte scenario, byte area);
    
    byte registerScenarioAreaLight(byte scenario, byte scenarioarea, byte light);
    
    void initialize();
    
    void processingLoop();
        
    void requestData(byte* data);
    
    void testSequenceStart();
    
    void testSequenceStop();
    
    void switchLight(byte area, byte light, bool on);
    
    void switchAllLights(bool on);
    
    void activateScenario(int scenario);
    
    void activateFirstScenario();
    
    void activateNoScenario();
    
    bool isLightOn(byte area, byte light);

    void toogleLight(byte area, byte light);
    
    void setLightSensorData(byte id);
};

#endif /* NGCandleArchUnitControl_h */
