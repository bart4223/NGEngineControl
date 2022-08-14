//
//  NGJoystickControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 13.08.22.
//

#ifndef NGJoystickControl_h
#define NGJoystickControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define DEFJOYSTICKPINX     A0
#define DEFJOYSTICKPINY     A1
#define DEFJOYSTICKPINFIRE  2

#define MAXJOYSTICKACTIONS  5
#define DEFTRIGGERDELAY     100
#define NOJOYSTICKDELAY     0
#define NOJOYSTICKTHRESHOLD 0

enum joystickAxis { jaNone, jaX, jaY };
enum joystickThresholdKind { jtkNone, jtkLess, jtkGreater };
enum joystickActionMode { jamTriggerLOW, jamTriggerHIGH };

struct joystickActionStruct
{
    int pin;
    joystickThresholdKind kind;
    int threshold;
    int delay;
    long int lastFire = 0;
    joystickActionMode mode;
    joystickAxis axis;
};
typedef struct joystickActionStruct joystickAction;

class NGJoystickControl {

private:
    byte _joystickPinX;
    byte _joystickPinY;
    byte _joystickPinFire;
    int _currentX;
    int _currentY;
    joystickAction _joystickActions[MAXJOYSTICKACTIONS];
    int _joystickActionCount = 0;
    
protected:
    void _create(byte joystickPinX, byte joystickPinY, byte joystickPinFire);
    
public:
    NGJoystickControl();
    
    NGJoystickControl(byte joystickPinX, byte joystickPinY, byte joystickPinFire);
    
    void initialize();
    
    void registerAction(int pin, joystickActionMode mode);
    
    void registerAction(int pin, joystickActionMode mode, int delay);
    
    void registerAction(int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold);
    
    void registerAction(int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, int delay);
    
    void processingLoop();
    
    int getX();
    
    int getY();
};

#endif /* NGJoystickControl_h */
