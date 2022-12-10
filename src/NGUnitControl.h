//
//  NGUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 13.05.21.
//

#ifndef NGUnitControl_h
#define NGUnitControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomUnitControl.h>
#include <NGJointControl.h>
#include <NGGripperControl.h>

#define _VERSION "1.2"
#define VERSION (char*)_VERSION

#define COMMANDDELAY 200

#define ENGINECOUNT  3
#define JOINTCOUNT   3
#define GRIPPERCOUNT 3
#define COMMANDCOUNT 5

#define DEFAULTJOINTMOVESTEP 10

enum commandKind { ckNone, ckJointSimulate, ckGripperSimulate };

struct commandDataStruct
{
    char* command;
    commandKind kind;
    char* name;
};
typedef struct commandDataStruct commandData;

struct engineDataStruct
{
    char* name;
    int initSpeed;
};
typedef struct engineDataStruct engineData;

struct jointDataStruct
{
    char* name;
    int minRad;
    int maxRad;
    int targetRad;
    bool simulate;
    int movestep;
};
typedef struct jointDataStruct jointData;

struct gripperDataStruct
{
    char* name;
    int minSpeed;
    int maxSpeed;
    bool simulate;
};
typedef struct gripperDataStruct gripperData;

#define ExceptionTooMuchCommandCount    200
#define ExceptionTooMuchEngineCount     201
#define ExceptionTooMuchJointCount      202
#define ExceptionTooMuchGripperCount    203

class NGUnitControl : public NGCustomUnitControl {
    
private:
    commandData _commandData[COMMANDCOUNT];
    int _commandCount = 0;
    NGEngineControl *_engines[ENGINECOUNT];
    engineData _engineData[ENGINECOUNT];
    int _enginesCount = 0;
    NGJointControl *_joints[JOINTCOUNT];
    jointData _jointData[JOINTCOUNT];
    int _jointsCount = 0;
    NGGripperControl *_grippers[GRIPPERCOUNT];
    gripperData _gripperData[GRIPPERCOUNT];
    int _grippersCount = 0;
    
protected:
    void _create(char* name, byte address, int serialRate);
    
    void _nop();

    void _processingReceivedData();
    
    void _processingReceivedDataNone();
    
    void _processingReceivedDataEngine();
    
    void _processingReceivedDataJoint();
    
    void _processingReceivedDataGripper();
    
    bool _processingCommand();
    
    void _processingStartupLoop();
    
    int _getNameSizeFromReceivedData();
    
    int _getEngineIndex(char* name);
    
    int _getJointIndex(char* name);
    
    int _getGripperIndex(char* name);
        
public:
    NGUnitControl();
    
    NGUnitControl(char* name);
                  
    NGUnitControl(char* name, byte address);
    
    NGUnitControl(char* name, byte address, int serialRate);

    void initialize();
    
    void processingLoop();
    
    void registerCommand(char* command, commandKind kind, char* name);
    
    void registerEngine(char* name, NGEngineControl *engine);
    
    void registerEngine(char* name, NGEngineControl *engine, int initSpeed);
    
    void engineRun(char* name, engineDirection direction);
    
    void engineStop(char* name);
    
    void engineSetSpeed(char* name, int speed);
    
    void registerJoint(char* name, NGJointControl *joint, int minRad, int maxRad);
    
    void registerJoint(char* name, NGJointControl *joint, int minRad, int maxRad, int maxMoveTicks);
    
    void registerJoint(char* name, NGJointControl *joint, int minRad, int maxRad, int maxMoveTicks, int engine);
    
    void registerJoint(char* name, NGJointControl *joint, int minRad, int maxRad, int maxMoveTicks, int engine, int movestep);
    
    int jointRead(char* name);
    
    int jointGetMinRad(char* name);
    
    int jointGetMaxRad(char* name);
    
    bool jointMove(char* name, int targetRad);
    
    bool jointMoveZero(char* name);
    
    void jointMoveStepToMax(char* name);
    
    void jointMoveStepToMin(char* name);
    
    bool jointIsMoving(char* name);
    
    void jointSimulate(char* name);
    
    void jointSetMaxSpeed(char* name, int speed);
    
    void jointSetTransducerThreshold(char* name, int threshold);
    
    void registerGripper(char* name, NGGripperControl *gripper, int minSpeed, int maxSpeed);
    
    void gripperGrip(char* name);
    
    void gripperRelease(char* name);
    
    void gripperSimulate(char* name);

    void requestData(byte* data);
};

#endif /* NGUnitControl_h */
