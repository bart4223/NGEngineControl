//
//  NGJointControl.h
//  NGEngineControl
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
#define JOINT_1_TRANSDUCER  1
#define JOINT_2             2
#define JOINT_2_TRANSDUCER  2

#define TRANSDUCERTHRESHOLD   3
#define ENGINEMOVEDELAY      20
#define DEFAULTENGINE        -1
#define DEFAULTMAXMOVETICKS   0

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
    int _maxMoveTicks = DEFAULTMAXMOVETICKS;
    
protected:
    void _create(int joint, int engine, int serialRate);

public:
    NGJointControl();
    
    NGJointControl(int joint);
    
    NGJointControl(int joint, int engine);
    
    NGJointControl(int joint, int engine, int serialRate);
    
    void initialize(int minRad, int maxRad);
    
    void initialize(int minRad, int maxRad, int maxSpeed);
    
    void initialize(char* name, int minRad, int maxRad);
    
    void initialize(char* name, int minRad, int maxRad, int maxSpeed);
    
    void setMinJointRad(int value);

    int getMinJointRad();
    
    void setMaxJointRad(int value);
    
    int getMaxJointRad();
    
    void setMaxSpeed(int value);
    
    void setMaxMoveTicks(int value);

    int getMaxSpeed();
    
    void setLogging(bool logging);
    
    void setTransducerThreshold(int threshold);
    
    char* getName();
    
    int read();
    
    bool move(int targetRad);
    
    bool moveZero();
    
    void simulate();
   
};

#endif /* NGJointControl_h */
