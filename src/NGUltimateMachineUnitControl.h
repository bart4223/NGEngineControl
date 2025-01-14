//
//  NGUltimateMachineUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 23.06.24.
//

#ifndef NGUltimateMachineUnitControl_h
#define NGUltimateMachineUnitControl_h

// Process Description
// 1. Turn on Arduino with S0
// 2. Arduino boots up and turn on power switch relais
// 3. Servo moves finger to switch off S0
// 4. Servo moves finger to starting position
// 5. Power switch relais turn off
// 6. Arduino shut down

#include <Arduino.h>
#include <NGCustomUnitControl.h>
#include <NGRelaisControl.h>
#include <NGServoControl.h>

#define _VERSION "0.6"
#define VERSION (char*)_VERSION

#define DEFAULTPINPOWERSWITCH   2
#define DEFAULTPINFINGER        8

#define DEFAULTZEROPOSITIONFINGER   90
#define DEFAULTMINPOSITIONFINGER     0
#define DEFAULTMAXPOSITIONFINGER   180
#define DEFAULTSTEPWIDTHFINGER       1

#define DEFAULTPROCESSDELAY 100

class NGUltimateMachineUnitControl : public NGCustomUnitControl {
    
private:
    NGRelaisControl *_powerSwitch;
    NGServoControl *_finger;
    byte _processStep = 0;
    long _lastProcessStep;
    int _processDelay = DEFAULTPROCESSDELAY;
    
protected:
    void _create(char* name, byte address, int serialRate, byte pinPowerSwitch, byte pinFinger, byte zeroPositionFinger, byte minPositionFinger, byte maxPositionFinger, byte stepWidthFinger);
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
    void _processingIRRemoteData();

public:
    NGUltimateMachineUnitControl();

    NGUltimateMachineUnitControl(char* name, byte pinPowerSwitch, byte pinFinger, byte zeroPositionFinger, byte minPositionFinger, byte maxPositionFinger, byte stepWidthFinger);
                  
    NGUltimateMachineUnitControl(char* name, byte address, byte pinPowerSwitch, byte pinFinger, byte zeroPositionFinger, byte minPositionFinger, byte maxPositionFinger, byte stepWidthFinger);
    
    NGUltimateMachineUnitControl(char* name, byte address, int serialRate, byte pinPowerSwitch, byte pinFinger, byte zeroPositionFinger, byte minPositionFinger, byte maxPositionFinger, byte stepWidthFinger);
    
    void setProcessDelay(int delay);
    
    void initialize();
    
    void processingLoop();
        
    void requestData(byte* data);
};

#endif /* NGUltimateMachineUnitControl_h */
