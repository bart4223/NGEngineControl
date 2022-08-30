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

#define _VERSION "0.2"
#define VERSION (char*)_VERSION

#define MAXWIRELESSREMOTECONTROLCOUNT 3

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
    
    void addJoystickAction(byte joystick, int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, int delay);
    
    void initialize();
    
    void processingLoop();
    
    void requestData(byte* data);
};

#endif /* NGWirelessRemoteUnitControl_h */
