//
//  NGCarSteeringControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 10.08.22.
//

#ifndef NGCarSteeringControl_h
#define NGCarSteeringControl_h

#include <Arduino.h>
#include <NGServoControl.h>
#include <NGCustomSteeringControl.h>

class NGCarSteeringControl : public NGCustomSteeringControl {

private:
    NGEngineControl *_engine;
    NGServoControl *_steering;

protected:
    void _create(int engine, int serialRate, byte pinSteering, byte steeringZeroPos, byte steeringMin, byte steeringMax, byte steeringStepWith);

public:
    NGCarSteeringControl();
    
    NGCarSteeringControl(byte pinSteering, byte steeringZeroPos, byte steeringMin, byte steeringMax, byte steeringStepWith);
    
    NGCarSteeringControl(int engine, byte pinSteering, byte steeringZeroPos, byte steeringMin, byte steeringMax, byte steeringStepWith);

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

#endif /* NGCarSteeringControl_h */
