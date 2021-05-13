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

#define STEPWIDTH 10
#define NULLSPEED  0
#define MINSPEED  20
#define MAXSPEED 255

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
