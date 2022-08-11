//
//  NGCarSteeringControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 10.08.22.
//

#ifndef NGCarSteeringControl_h
#define NGCarSteeringControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomSteeringControl.h>

class NGCarSteeringControl : public NGCustomSteeringControl {

private:
    NGEngineControl _engine = NGEngineControl();

protected:
    void _create(int engine, int serialRate);

public:
    NGCarSteeringControl();
    
    NGCarSteeringControl(int engine);

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
