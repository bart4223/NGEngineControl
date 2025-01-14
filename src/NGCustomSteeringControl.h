//
//  NGCustomSteeringControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 10.08.22.
//

#ifndef NGCustomSteeringControl_h
#define NGCustomSteeringControl_h

#include <Arduino.h>
#include <NGEngineControl.h>

enum turnDirection { tdNone, tdLeft, tdRight, tdLeftSoft, tdRightSoft };

class NGCustomSteeringControl {

protected:
    bool _initialized = false;
    bool _logging = true;
    byte _speed = 0;
    
public:
    void setLogging(bool logging);
    
    bool getLogging();
    
    virtual void initialize();
    
    virtual void stop();
    
    virtual void runFullSpeedForward();
    
    virtual void runFullSpeedBackward();
    
    virtual void run(engineDirection direction);
    
    virtual void run(engineDirection direction, byte speed);
    
    virtual void turnForward(turnDirection turn);
    
    virtual void turnForward(turnDirection turn, byte speed);
    
    virtual void turnBackward(turnDirection turn);
    
    virtual void turnBackward(turnDirection turn, byte speed);
};

#endif /* NGCustomSteeringControl_h */
