//
//  NGCentralUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 11.06.21.
//

#ifndef NGCentralUnitControl_h
#define NGCentralUnitControl_h

#include <Arduino.h>
#include <NGExceptionDefinitions.h>
#include <NGCustomUnitControl.h>

#define _VERSION "2.0"
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

#define MOTIONPROFILECOUNT           2
#define MOTIONPROFILECOMPONENTCOUNT  5
#define MOTIONPROFILEITEMCOUNT      20

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

class NGCentralUnitControl : public NGCustomUnitControl {
  
private:
    unit _unit[UNITCOUNT];
    int _unitCount = 0;
    component _component[COMPONENTCOUNT];
    int _componentCount = 0;
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
};

#endif /* NGCentralUnitControl_hpp */
