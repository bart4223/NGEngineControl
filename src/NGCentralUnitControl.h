//
//  NGCentralUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 11.06.21.
//

#ifndef NGCentralUnitControl_h
#define NGCentralUnitControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGExceptionDefinitions.h>
#include <NGCustomUnitControl.h>

#define _VERSION "1.7"
#define VERSION (char*)_VERSION

#define OBSERVEMEMORYDELAY 5000

#define UNITCOUNT       3
#define COMPONENTCOUNT  6

#define NOUNITADDRESS  0x00

#define CNOSTEPWIDTH     0
#define CDEFSTEPWIDTH   10

#define NOCURRENTCOMPONENT  -1
#define CNOTARGETPOSITION   -1
#define NOPROFILE           -1
#define NOPROFILESEQUENCE   -1

#define CNODELAY 0

#define CGRIPPERGRIP         0
#define CGRIPPERRELEASE      1

#define IRFUNCCOUNT      10
#define IRFUNCMENUDELAY 100

#define MOTIONPROFILECOUNT           2
#define MOTIONPROFILECOMPONENTCOUNT  5
#define MOTIONPROFILEITEMCOUNT      20

#define IRP_APPLE       0x14
#define IRP_APPLE_2     0x15
#define IRA_APPLE       0xA3
#define IRC_APPLE_MENU  0x02
#define IRC_APPLE_LEFT  0x08
#define IRC_APPLE_RIGHT 0x07
#define IRC_APPLE_UP    0x0B
#define IRC_APPLE_DOWN  0x0D
#define IRC_APPLE_OK    0x5D
#define IRC_APPLE_PLAY  0x5E

enum functionType { ftMenu, ftLeft, ftRight, ftUp, ftDown, ftOK, ftPlay };

struct irremotefuncStruct
{
    byte protocol;
    byte address;
    byte command;
    functionType type;
};
typedef struct irremotefuncStruct irremotefunc;

struct unitStruct
{
    char* name;
    byte address;
};
typedef struct unitStruct unit;

enum componentType { ctNone, ctEngine, ctJoint, ctGripper, ctMotionProfile };

struct motionProfileComponentStruct
{
    componentType type;
    char* name;
};
typedef struct motionProfileComponentStruct motionProfileComponent;

struct motionProfileItemStruct
{
    byte component;
    int position;
    int delay;
};
typedef struct motionProfileItemStruct motionProfileItem;

struct motionProfileStruct
{
    motionProfileComponent components[MOTIONPROFILECOMPONENTCOUNT];
    int componentCount;
    motionProfileItem items[MOTIONPROFILEITEMCOUNT];
    int itemCount;
    bool infinite;
    int sequence;
};
typedef struct motionProfileStruct motionProfile;

struct componentStruct
{
    char* unit;
    char* component;
    componentType type;
    int position;
    int min;
    int max;
    int targetposition;
    int profile;
    bool play;
    int stepwidth;
};
typedef struct componentStruct component;

struct irremoteStruct
{
    byte protocol;
    byte address;
    byte command;
};
typedef struct irremoteStruct irremote;

class NGCentralUnitControl : public NGCustomUnitControl {
  
private:
    unit _unit[UNITCOUNT];
    int _unitCount = 0;
    component _component[COMPONENTCOUNT];
    int _componentCount = 0;
    irremote _irremotedata;
    bool _irremotedataReceived = false;
    irremotefunc _irremotefunc[IRFUNCCOUNT];
    int _irremotefuncCount = 0;
    int _currentComponent = NOCURRENTCOMPONENT;
    motionProfile _motionProfile[MOTIONPROFILECOUNT];
    int _motionProfileCount = 0;

protected:
    void _create(char* name, byte address, int serialRate);
    
    byte _getUnitAddress(char* name);
    
    int _prepareCommand(byte subject, byte operation, char* name, byte command[]);
    
    void _processingReceivedData();
    
    void _processingIRRemoteData();
    
    void _processingStartupLoop();
    
public:
    NGCentralUnitControl();
    
    NGCentralUnitControl(char* name);
    
    NGCentralUnitControl(char* name, byte address);
    
    NGCentralUnitControl(char* name, byte address, int serialRate);
    
    void initialize();
    
    void processingLoop();
    
    void registerUnit(char* name);
    
    void registerUnit(char* name, byte address);
    
    void registerComponent(componentType type, char* unit, char* comp);
    
    void registerComponent(componentType type, char* unit, char* comp, int stepwidth);
    
    int registerMotionProfile(char* profile, char* unit);
    
    int registerMotionProfile(char* profile, char* unit, bool infinite);
    
    int addMotionProfileComponent(int profile, componentType type, char* comp);
    
    void addMotionProfileItem(int profile, int component, int position);
    
    void addMotionProfileItem(int profile, int component, int position, int delay);
    
    void registerIRRemoteFunction(functionType type, byte protocol, byte address, byte command);
    
    void sendUnitEngineRunForward(char* name, char* engine);

    void sendUnitEngineRunBackward(char* name, char* engine);
    
    void sendUnitEngineStop(char* name, char* engine);
    
    void sendUnitEngineSetSpeed(char* name, char* engine, int speed);
    
    void sendUnitJointMove(char* name, char* joint, int targetrad);
    
    void sendUnitJointSimulate(char* name, char* joint);
    
    void sendUnitJointMoveStepToMax(char* name, char* joint);
    
    void sendUnitJointMoveStepToMin(char* name, char* joint);
    
    int receiveUnitJointRead(char* name, char* joint);
    
    void sendUnitGripperRelease(char* name, char* gripper);

    void sendUnitGripperGrip(char* name, char* gripper);
    
    void sendUnitGripperSimulate(char* name, char* gripper);

    bool sendUnitCommand(char* name, byte command[], int commandsize);

    void receiveUnitData(char* name);
    
    void requestData(byte* data);
    
    void setIRRemoteData(byte protocol, byte address, byte command);
};

#endif /* NGCentralUnitControl_hpp */
