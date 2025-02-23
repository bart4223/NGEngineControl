//
//  NGDoorGuardUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 18.02.25.
//

#ifndef NGDoorGuardUnitControl_h
#define NGDoorGuardUnitControl_h

#include <Arduino.h>
#include <NGCustomUnitControl.h>
#include <NGHallSensor.h>
#include <NGIEffect.h>

#define _VERSION "0.4"
#define VERSION (char*)_VERSION

struct doorItemStruct
{
    NGHallSensor *sensor;
    NGIEffect *effectOpen;
    NGIEffect *effectClose;
    bool closed;
};
typedef struct doorItemStruct doorItem;

#define MAXDOORITEMCOUNT 3

class NGDoorGuardUnitControl : public NGCustomUnitControl {

private:
    doorItem _doors[MAXDOORITEMCOUNT];
    byte _doorCount = 0;

protected:
    void _create(char* name, byte address, int serialRate);

    void _processingReceivedData();
    
    void _processingStartupLoop();
    
    void _processingIRRemoteData();

    void _logDoorState(byte door, bool closed);

public:
    NGDoorGuardUnitControl();
    
    NGDoorGuardUnitControl(char* name);
                  
    NGDoorGuardUnitControl(char* name, byte address);
    
    NGDoorGuardUnitControl(char* name, byte address, int serialRate);
    
    byte registerDoor(NGHallSensor *sensor, NGIEffect *effectopen, NGIEffect *effectclose);
    
    void initialize();
    
    void processingLoop();
    
    void requestData(byte* data);
};

#endif /* NGDoorGuardUnitControl_h */