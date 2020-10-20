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

enum direction { FORWARD, BACKWARD };

class NGEngineControl {
   
private:
    int _engine;
    int _forwardPin;
    int _backwardPin;
    int _speed;
    int _serialRate;
    bool _initialized;
    
public:
    NGEngineControl(int engine, int serialRate);
    
    void initialize();
    
    void setSpeed(int speed);
    
    bool run(direction direction);
    
    bool stop();
};

#endif /* NGEngineControl_h */
