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

class NGUnitControl {
    
private:
    bool _initialized;
    bool _logging;
    int _serialRate;
    char* _name;
    NGJointControl _joints[3];
    unsigned int _jointsCount = 0;
    NGGripperControl _grippers[3];
    gripperData _gripperData[3];
    unsigned int _grippersCount = 0;
    
protected:
    void _create(char* name, int serialRate);
    int getGripperIndex(char* name);
    
public:
    NGUnitControl();
    
    NGUnitControl(char* name);
    
    NGUnitControl(char* name, int serialRate);

    void initialize();
    
    void registerGripper(char* name, int engine, int minSpeed, int maxSpeed);
    
    void gripperGrip(char* name);
    
    void gripperRelease(char* name);

};

#endif /* NGUnitControl_h */
