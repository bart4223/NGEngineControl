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

void _unitWireReceiveEvent(int byteCount);

void _unitWireRequestEvent();

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
};
typedef struct jointDataStruct jointData;

struct gripperDataStruct
{
    char* name;
    int minSpeed;
    int maxSpeed;
};
typedef struct gripperDataStruct gripperData;

class NGUnitControl : public NGCustomUnitControl {
    
private:
    NGEngineControl *_engines[3];
    engineData _engineData[3];
    int _enginesCount = 0;
    NGJointControl *_joints[3];
    jointData _jointData[3];
    int _jointsCount = 0;
    NGGripperControl *_grippers[3];
    gripperData _gripperData[3];
    int _grippersCount = 0;
    
protected:
    void _create(char* name, byte address, int serialRate);
    
    void _nop();

    void _processingReceivedData();
    
    void _processingReceivedDataNone();
    
    void _processingReceivedDataEngine();
    
    void _processingReceivedDataJoint();
    
    void _processingReceivedDataGripper();
    
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
    
    void registerEngine(char* name, NGEngineControl *engine);
    
    void registerEngine(char* name, NGEngineControl *engine, int initSpeed);
    
    void engineRun(char* name, engineDirection direction);
    
    void engineStop(char* name);
    
    void engineSetSpeed(char* name, int speed);
    
    void registerJoint(char* name, NGJointControl *joint, int minRad, int maxRad);
    
    void registerJoint(char* name, NGJointControl *joint, int minRad, int maxRad, int maxMoveTicks);
    
    void registerJoint(char* name, NGJointControl *joint, int minRad, int maxRad, int maxMoveTicks, int engine);
    
    void jointRead(char* name);
    
    bool jointMove(char* name, int targetRad);
    
    bool jointIsMoving(char* name);
    
    void jointSimulate(char* name);
    
    void registerGripper(char* name, NGGripperControl *gripper, int minSpeed, int maxSpeed);
    
    void gripperGrip(char* name);
    
    void gripperRelease(char* name);

};

#endif /* NGUnitControl_h */
