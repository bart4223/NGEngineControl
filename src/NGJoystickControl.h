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

#define NOJOYSTICKID    -1

enum joystickAxis { jaNone, jaX, jaY };
enum joystickThresholdKind { jtkNone, jtkLess, jtkGreater };
enum joystickActionMode { jamTriggerLOW, jamTriggerHIGH };

enum joystickMovement { jmNone, jmUp, jmDown, jmLeft, jmRight, jmFire };

typedef void (*joystickActionCallbackFunc)(int id, joystickMovement joystickmovement);

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
    int _id = NOJOYSTICKID;
    bool _logging = false;
    joystickActionCallbackFunc _actionCallback = nullptr;

protected:
    void _create(int id, byte joystickPinX, byte joystickPinY, byte joystickPinFire);
    
public:
    NGJoystickControl();
    
    NGJoystickControl(int id);
    
    NGJoystickControl(byte joystickPinX, byte joystickPinY, byte joystickPinFire);
    
    void initialize();
    
    void setLogging(bool logging);
    
    void registerActionCallback(joystickActionCallbackFunc callback);
    
    void registerAction(int pin, joystickActionMode mode);
    
    void registerAction(int pin, joystickActionMode mode, int delay);
    
    void registerAction(int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold);
    
    void registerAction(int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, int delay);
    
    void processingLoop();
    
    int getID();
    
    int getX();
    
    int getY();
};

#endif /* NGJoystickControl_h */
