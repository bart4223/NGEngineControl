//
//  NGWirelessRemoteUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 13.08.22.
//

#ifndef NGWirelessRemoteUnitControl_h
#define NGWirelessRemoteUnitControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomUnitControl.h>
#include <NGJoystickControl.h>

#define _VERSION "0.7"
#define VERSION (char*)_VERSION

#define MAXWIRELESSREMOTECONTROLCOUNT 3
#define DEFLASTINFODELAY 500

enum wirelessRemoteControlKind { wrckJoystick };

struct wirelessRemoteControlStruct
{
    wirelessRemoteControlKind kind;
    NGJoystickControl *joystick;
    char* name;
};
typedef struct wirelessRemoteControlStruct wirelessRemoteControl;

class NGWirelessRemoteUnitControl : public NGCustomUnitControl {

private:
    wirelessRemoteControl _remoteControls[MAXWIRELESSREMOTECONTROLCOUNT];
    int _remoteControlCount = 0;
    int _lastInfoID = -1;
    long int _lastInfo = -1;
    int _lastInfoDelay = DEFLASTINFODELAY;
    
protected:
    void _create(char* name, byte address, int serialRate);
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
    void _processingIRRemoteData();
    
public:
    NGWirelessRemoteUnitControl();
    
    NGWirelessRemoteUnitControl(char* name);
                  
    NGWirelessRemoteUnitControl(char* name, byte address);
    
    NGWirelessRemoteUnitControl(char* name, byte address, int serialRate);
    
    byte registerJoystick();
    
    byte registerJoystick(char* name);
    
    byte registerJoystick(char* name, byte joystickPinX, byte joystickPinY, byte joystickPinFire);
    
    void addJoystickAction(byte joystick, int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, int delay, joystickMovement movement);
    
    void setLastInfoDelay(int lastinfodelay);
    
    void initialize();
    
    void processingLoop();
    
    void requestData(byte* data);
};

#endif /* NGWirelessRemoteUnitControl_h */
