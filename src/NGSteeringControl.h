//
//  NGSteeringControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 26.08.21.
//

#ifndef NGSteeringControl_h
#define NGSteeringControl_h

#include <Arduino.h>
#include <NGCustomSteeringControl.h>
#include <NGEngineControl.h>

#define ENGINENULLOFFSET 0

class NGSteeringControl : public NGCustomSteeringControl {

private:
    NGEngineControl _engineLeft = NGEngineControl();
    NGEngineControl _engineRight = NGEngineControl();
    int _offsetEngineLeft = 0;
    int _offsetEngineRight = 0;

protected:
    void _create(int engineLeft, int engineRight, int serialRate, int offsetEngineLeft, int offsetEngineRight);
    
    byte _calcEngineSpeed(byte speed, int offset);
    
public:
    NGSteeringControl();
    
    NGSteeringControl(int engineLeft, int engineRight);
    
    NGSteeringControl(int engineLeft, int engineRight, int offsetEngineLeft, int offsetEngineRight);
    
    NGSteeringControl(int engineLeft, int engineRight, int serialRate);
    
    NGSteeringControl(int engineLeft, int engineRight, int serialRate, int offsetEngineLeft, int offsetEngineRight);
    
    void initialize();
    
    void stop();
    
    void run(engineDirection direction, byte speed);
    
    void turnForward(turnDirection turn, byte speed);
    
    void turnBackward(turnDirection turn, byte speed);
    
    void runFullSpeedForward();

    void runFullSpeedBackward();

    void run(engineDirection direction);

    void turnForward(turnDirection turn);

    void turnBackward(turnDirection turn);
      
};

#endif /* NGSteeringControl_h */
