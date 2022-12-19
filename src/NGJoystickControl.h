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
#define NOLASTACTIONID  -1

#define NOJOYSTICKACTIONPIN -1

enum joystickAxis { jaNone, jaX, jaY };
enum joystickThresholdKind { jtkNone, jtkLess, jtkGreater };
enum joystickActionMode { jamNone, jamTriggerLOW, jamTriggerHIGH };

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
    joystickMovement movement;
    int triggerDelay = DEFTRIGGERDELAY;
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
    int _lastAction = NOLASTACTIONID;

protected:
    void _create(int id, byte joystickPinX, byte joystickPinY, byte joystickPinFire);
    
public:
    NGJoystickControl();
    
    NGJoystickControl(int id);
    
    NGJoystickControl(byte joystickPinX, byte joystickPinY, byte joystickPinFire);
    
    NGJoystickControl(int id, byte joystickPinX, byte joystickPinY, byte joystickPinFire);
    
    void initialize();
    
    void setLogging(bool logging);
    
    bool getLogging();
    
    void registerActionCallback(joystickActionCallbackFunc callback);
    
    void registerAction(joystickAxis axis, joystickThresholdKind kind, int threshold, int delay, joystickMovement movement);
    
    void registerAction(int pin, joystickActionMode mode, joystickMovement movement);
    
    void registerAction(int delay, joystickMovement movement);
    
    void registerAction(int pin, joystickActionMode mode, int delay, joystickMovement movement);
    
    void registerAction(int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, joystickMovement movement);
    
    void registerAction(int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, int delay, joystickMovement movement);
    
    void registerAction(int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, int delay, joystickMovement movement, int triggerdelay);
    
    void processingLoop();
    
    int getID();
    
    int getX();
    
    int getY();
    
    bool hasLastMovement();

    joystickMovement getLastMovement();
};

#endif /* NGJoystickControl_h */
