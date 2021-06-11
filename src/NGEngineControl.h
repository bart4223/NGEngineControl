//
//  NGEngineControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 18.10.20.
//

#ifndef NGEngineControl_h
#define NGEngineControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define ENGINE_0           0
#define ENGINE_0_FORWARD  10
#define ENGINE_0_BACKWARD 11
#define ENGINE_1           1
#define ENGINE_1_FORWARD   3
#define ENGINE_1_BACKWARD  9
#define ENGINE_2           2
#define ENGINE_2_FORWARD   5
#define ENGINE_2_BACKWARD  6
#define ENGINE_3           3
#define ENGINE_3_FORWARD   8
#define ENGINE_3_BACKWARD  7

#define STEPWIDTH              10
#define NULLSPEED               0
#define MINSPEED               20
#define MAXSPEED              255
#define NULLINTERVAL            0
#define NULLSTEPS               0

enum engineDirection { edNone, edForward, edBackward };

class NGEngineControl {
   
private:
    int _engine;
    int _forwardPin;
    int _backwardPin;
    int _speed;
    int _serialRate;
    int _interval;
    bool _initialized;
    bool _running;
    bool _logging;
    engineDirection _direction;

protected:
    void _create(int engine, int serialRate);
    void _slowDown(int startSpeed, int targetSpeed, int interval);
    void _speedUp(int startSpeed, int targetSpeed);
    void _setSpeed(int pin, int speed);

public:
    NGEngineControl();
    
    NGEngineControl(int engine);
    
    NGEngineControl(int engine, int serialRate);
    
    void initialize();
    
    void initialize(int speed);
    
    void setLogging(bool logging);
    
    void setSpeed(int speed);

    void setSpeed(int speed, int interval);

    bool run(engineDirection direction);
    
    bool stop();

    bool stop(int interval);
    
};

#endif /* NGEngineControl_h */
