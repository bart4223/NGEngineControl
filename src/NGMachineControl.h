//
//  NGMachineControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 13.05.21.
//

#ifndef NGMachineControl_h
#define NGMachineControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGEngineControl.h>
#include <NGJointControl.h>
#include <NGGripperControl.h>

struct gripperDataStruct
{
    char* name;
    int minSpeed;
    int maxSpeed;
};
typedef struct gripperDataStruct gripperData;

class NGMachineControl {
    
private:
    bool _initialized;
    bool _logging;
    int _serialRate;
    NGJointControl *_joints[3];
    unsigned int _jointsCount = 0;
    NGGripperControl _grippers[3];
    gripperData _gripperData[3];
    unsigned int _grippersCount = 0;
    
protected:
    void _create(int serialRate);
    int getGripperIndex(char* name);
    
public:
    NGMachineControl();
    
    NGMachineControl(int serialRate);

    void initialize();
    
    void registerGripper(char* name, int engine, int minSpeed, int maxSpeed);
    
    void gripperGrip(char* name);
    
    void gripperRelease(char* name);

};

#endif /* NGMachineControl_h */
