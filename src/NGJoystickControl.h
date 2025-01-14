//
//  NGJoystickControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 13.08.22.
//

#ifndef NGJoystickControl_h
#define NGJoystickControl_h

#include <Arduino.h>

#define DEFJOYSTICKPINX     A0
#define DEFJOYSTICKPINY     A1
#define DEFJOYSTICKPINFIRE  2

#define MAXJOYSTICKACTIONS  5
#define DEFTRIGGERDELAY     100
#define DEFMAPPING          255
#define NOJOYSTICKDELAY     0
#define NOJOYSTICKTHRESHOLD 0

#define NOJOYSTICKID    -1
#define NOLASTACTIONID  -1

#define NOJOYSTICKACTIONPIN -1

enum joystickKind { jkAnalog, jkDigital };
enum joystickAxis { jaNone, jaX, jaY };
enum joystickThresholdKind { jtkNone, jtkLess, jtkGreater };
enum joystickActionMode { jamNone, jamTriggerLOW, jamTriggerHIGH, jamMapping, jamMappingInvers };

enum joystickMovement { jmNone, jmUp, jmDown, jmLeft, jmRight, jmFire };

typedef void (*joystickActionCallbackFunc)(int id, joystickMovement joystickmovement);

typedef void (*joystickActionValueCallbackFunc)(int id, joystickMovement joystickmovement, int value);

struct joystickActionStruct
{
    int pin;
    joystickThresholdKind kind;
    int threshold;
    int delay;
    long int lastFire = 0;
    int continuousFire = 0;
    joystickActionMode mode;
    joystickAxis axis;
    joystickMovement movement;
    int triggerDelay = DEFTRIGGERDELAY;
    int mapping = DEFMAPPING;
    int lastValue = 0;
};
typedef struct joystickActionStruct joystickAction;

class NGJoystickControl {

private:
    byte _joystickPinX;
    byte _joystickPinY;
    byte _joystickPinX2;
    byte _joystickPinY2;
    byte _joystickPinFire;
    bool _joystickPinFireHigh = false;
    int _currentX;
    int _currentY;
    joystickAction _joystickActions[MAXJOYSTICKACTIONS];
    int _joystickActionCount = 0;
    int _id = NOJOYSTICKID;
    bool _logging = false;
    bool _logXAxis = false;
    bool _logYAxis = false;
    joystickActionCallbackFunc _actionCallback = nullptr;
    joystickActionValueCallbackFunc _actionValueCallback = nullptr;
    int _lastAction = NOLASTACTIONID;
    int _continuousFireThreshold = 0;
    joystickKind _kind;
    byte _digitalEpsilon = 0;

protected:
    void _create(joystickKind kind, int id, byte joystickPinX, byte joystickPinY, byte joystickPinX2, byte joystickPinY2, byte joystickPinFire, bool joystickPinFireHigh);
    
public:
    NGJoystickControl();
    
    NGJoystickControl(int id);
    
    NGJoystickControl(byte joystickPinX, byte joystickPinY, byte joystickPinFire);
    
    NGJoystickControl(int id, byte joystickPinX, byte joystickPinY, byte joystickPinFire);
    
    NGJoystickControl(int id, byte joystickPinXL, byte joystickPinXR, byte joystickPinYD, byte joystickPinYU, byte joystickPinFire);
    
    NGJoystickControl(int id, byte joystickPinXL, byte joystickPinXR, byte joystickPinYD, byte joystickPinYU, byte joystickPinFire, bool joystickPinFireHigh);
    
    void initialize();
    
    void setLogging(bool logging);
    
    bool getLogging();
    
    void setLogXAxis(bool logging);
    
    void setLogYAxis(bool logging);
    
    void setContinuousFireThreshold(int continuousfirethreshold);
    
    void registerActionCallback(joystickActionCallbackFunc callback);
    
    void registerActionValueCallback(joystickActionValueCallbackFunc callback);
    
    void registerAction(joystickAxis axis, joystickThresholdKind kind, int threshold, int delay, joystickMovement movement);
    
    void registerAction(int pin, joystickActionMode mode, joystickMovement movement);
    
    void registerAction(int delay, joystickMovement movement);
    
    void registerAction(int pin, joystickActionMode mode, int delay, joystickMovement movement);
    
    void registerAction(joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, int delay, joystickMovement movement);
    
    void registerAction(int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, joystickMovement movement);
    
    void registerAction(int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, int delay, joystickMovement movement);
    
    void registerAction(int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, int delay, joystickMovement movement, int triggerdelay);
    
    void processingLoop();
    
    int getID();
    
    int getX();
    
    int getY();
    
    bool hasLastMovement();

    joystickMovement getLastMovement();
    
    int getLastValue();
};

#endif /* NGJoystickControl_h */
