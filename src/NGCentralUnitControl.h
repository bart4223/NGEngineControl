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

#include <NGCustomUnitControl.h>

#define _VERSION "0.5"
#define VERSION (char*)_VERSION

#define OBSERVEMEMORYDELAY 5000

#define UNITCOUNT       3
#define COMPONENTCOUNT  5

#define IRFUNCCOUNT     10
#define IRFUNCMENUDELAY 100

#define IRP_APPLE       0x14
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

enum componentType { ctEngine, ctJoint, ctGripper };

struct componentStruct
{
    char* unit;
    char* component;
    componentType type;
    int position;
    int min;
    int max;
    int targetposition;
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
    int _currentComponent = -1;

protected:
    void _create(char* name, byte address, int serialRate);
    
    byte _getUnitAddress(char* name);

    int _prepareCommand(byte subject, byte operation, char* name, byte command[]);
    
    void _processingReceivedData();
    
    void _processingIRRemoteData();
    
public:
    NGCentralUnitControl();
    
    NGCentralUnitControl(char* name);
    
    NGCentralUnitControl(char* name, byte address);
    
    NGCentralUnitControl(char* name, byte address, int serialRate);
    
    void initialize();
    
    void processingLoop();
    
    void registerUnit(char* name, byte address);
    
    void registerComponent(componentType type, char* unit, char* comp);
    
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

    bool sendUnitCommand(char* name, byte command[], int commandsize);

    void receiveUnitData(char* name);
    
    void requestData(byte* data);
    
    void setIRRemoteData(byte protocol, byte address, byte command);
};

#endif /* NGCentralUnitControl_hpp */
