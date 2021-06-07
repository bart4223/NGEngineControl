//
//  NGUnitControl.h
//  NGUnitControl
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

#include <NGJointControl.h>
#include <NGGripperControl.h>

struct gripperDataStruct
{
    char* name;
    int minSpeed;
    int maxSpeed;
};
typedef struct gripperDataStruct gripperData;

struct jointDataStruct
{
    char* name;
    int minRad;
    int maxRad;
};
typedef struct jointDataStruct jointData;

class NGUnitControl {
    
private:
    bool _initialized;
    bool _logging;
    int _serialRate;
    char* _name;
    NGJointControl *_joints[3];
    jointData _jointData[3];
    int _jointsCount = 0;
    NGGripperControl *_grippers[3];
    gripperData _gripperData[3];
    int _grippersCount = 0;
    
protected:
    void _create(char* name, int serialRate);
    int getGripperIndex(char* name);
    int getJointIndex(char* name);
    
public:
    NGUnitControl();
    
    NGUnitControl(char* name);
    
    NGUnitControl(char* name, int serialRate);

    void initialize();
    
    void registerJoint(char* name, NGJointControl *joint, int minRad, int maxRad);
    
    void registerJoint(char* name, NGJointControl *joint, int minRad, int maxRad, int maxMoveTicks);
    
    void registerJoint(char* name, NGJointControl *joint, int minRad, int maxRad, int maxMoveTicks, int engine);
    
    void jointRead(char* name);
    
    bool jointMove(char* name, int targetRad);
    
    void jointSimulate(char* name);
    
    void registerGripper(char* name, NGGripperControl *gripper, int minSpeed, int maxSpeed);
    
    void gripperGrip(char* name);
    
    void gripperRelease(char* name);

};

#endif /* NGUnitControl_h */
