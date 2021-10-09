//
//  NGSteeringControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 26.08.21.
//

#ifndef NGSteeringControl_h
#define NGSteeringControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGEngineControl.h>

enum turnDirection { tdNone, tdLeft, tdRight };

class NGSteeringControl {

private:
    bool _initialized;
    bool _logging;
    byte _speed;
    NGEngineControl _engineLeft = NGEngineControl();
    NGEngineControl _engineRight = NGEngineControl();

protected:
    void _create(int engineLeft, int engineRight, int serialRate);
    
public:
    NGSteeringControl();
    
    NGSteeringControl(int engineLeft, int engineRight);
    
    NGSteeringControl(int engineLeft, int engineRight, int serialRate);
    
    void initialize();
    
    void stop();
    
    void runFullSpeedForward();
    
    void runFullSpeedBackward();
    
    void run(engineDirection direction);
    
    void run(engineDirection direction, byte speed);
    
    void turnForward(turnDirection turn);
    
    void turnForward(turnDirection turn, byte speed);
};

#endif /* NGSteeringControl_h */
