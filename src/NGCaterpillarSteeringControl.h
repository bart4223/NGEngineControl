//
//  NGCaterpillarSteeringControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 26.02.23.
//

#ifndef NGCaterpillarSteeringControl_h
#define NGCaterpillarSteeringControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomSteeringControl.h>

class NGCaterpillarSteeringControl : public NGCustomSteeringControl {

private:
    NGEngineControl *_engineRear;
    NGEngineControl *_engineBow;

protected:
    void _create(int engineRear, int engineBow, int serialRate);

public:
    NGCaterpillarSteeringControl();
    
    NGCarSteeringControl(int engineRear, int engineBow);

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
    
    bool isRunning();
};

#endif /* NGCaterpillarSteeringControl_h */
