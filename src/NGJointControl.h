//
//  NGJointControl.h
//  NGJointControl
//
//  Created by Nils Grimmer on 11.05.21.
//

#ifndef NGJointControl_h
#define NGJointControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGEngineControl.h>

#define JOINT_0             0
#define JOINT_0_TRANSDUCER  3
#define JOINT_1             1
#define JOINT_1_TRANSDUCER  4
#define JOINT_2             2
#define JOINT_2_TRANSDUCER  5

#define TRANSDUCERTHRESHOLD  3
#define ENGINEMOVEDELAY     20

enum jointDirection { jdNone, jdLeft, jdRight };

class NGJointControl {

private:
    int _joint;
    int _transducerPin;
    int _minJointRad;
    int _maxJointRad;
    int _currentJointRad;
    int _transducerThreshold = TRANSDUCERTHRESHOLD;
    int _maxSpeed;
    bool _initialized;
    bool _logging;
    char* _name;
    NGEngineControl _engine = NGEngineControl();
    int _engineMoveDelay = ENGINEMOVEDELAY;
    
protected:
    void _create(int joint, int serialRate);

public:
    NGJointControl(int joint);
    
    NGJointControl(int joint, int serialRate);
    
    void initialize(char* name, int minRad, int maxRad, int maxSpeed);
    
    void setMinJointRad(int value);

    int getMinJointRad();
    
    void setMaxJointRad(int value);
    
    int getMaxJointRad();
    
    void setMaxSpeed(int value);
    
    void setLogging(bool logging);
    
    char* getName();
    
    int read();
    
    void move(int targetRad);
    
    void simulate();
   
};

#endif /* NGJointControl_h */