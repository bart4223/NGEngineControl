//
//  NGCustomMotionControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 06.02.22.
//

#ifndef NGCustomMotionControl_h
#define NGCustomMotionControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCommon.h>
#include <NGCustomMotionMimic.h>
#include <NGSteeringControl.h>

class NGCustomMotionControl {
  
protected:
    NGSteeringControl *_steeringControl;
    NGCustomMotionMimic *_motionMimic = nullptr;

    virtual void _create(NGSteeringControl *steeringControl);
    
    void _initializeMotionMimic();
    
    void _initializeSteering();

public:
    void registerMotionMimic(NGCustomMotionMimic *mimic);
    
    bool hasMotionMimic();

    void initialize();
    
    int thinkingDelay();
    
    bool nextMotionSequenceNecessary(int closeness);
    
    motionSequenceKind determineNextMotionSequenceKind(int closeness);
    
    bool correctNextMotionSequenceKind();
    
    void steeringRun(engineDirection direction, int speed);
    
    void steeringStop();

    void steeringTurnForward(turnDirection turn);
    
    void steeringTurnBackward(turnDirection turn);
};

#endif /* NGCustomMotionControl_h */
    
