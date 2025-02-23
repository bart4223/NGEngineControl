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

#define _VERSION "0.8"
#define VERSION (char*)_VERSION

enum doorEffectKind{ dekInfinite, dekFinite };

struct doorItemStruct
{
    NGHallSensor *sensor;
    doorEffectKind effectKindOpen;
    NGIEffect *effectOpenOn;
    NGIEffect *effectOpenOff;
    doorEffectKind effectKindClose;
    NGIEffect *effectCloseOn;
    NGIEffect *effectCloseOff;
    bool closed;
    long lastEffect;
    int openDelay;
    int closeDelay;
};
typedef struct doorItemStruct doorItem;

#define MAXDOORITEMCOUNT 3
#define DEFDOOREFFECTDELAY 1000

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
    
    byte registerDoor(NGHallSensor *sensor, NGIEffect *effectopenOn, NGIEffect *effectcloseOn);
    
    byte registerDoor(NGHallSensor *sensor, doorEffectKind effectKindOpen, NGIEffect *effectopenOn,  doorEffectKind effectKindClose, NGIEffect *effectcloseOn);
    
    byte registerDoor(NGHallSensor *sensor, doorEffectKind effectKindOpen, NGIEffect *effectopenOn,  NGIEffect *effectopenOff, doorEffectKind effectKindClose, NGIEffect *effectcloseOn, NGIEffect *effectcloseOff);
    
    void setDoorDelay(byte door, int delayOpen);

    void setDoorDelay(byte door, int delayOpen, int delayClose);
    
    void initialize();
    
    void processingLoop();
    
    void requestData(byte* data);
};

#endif /* NGDoorGuardUnitControl_h */