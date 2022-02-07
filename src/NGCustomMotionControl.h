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

class NGCustomMotionControl {
  
private:
    NGCustomMotionMimic *_motionMimic = nullptr;
    
protected:
    virtual void _create();
    
    void _initializeMotionMimic();
    
public:
    void registerMotionMimic(NGCustomMotionMimic *mimic);
    
    bool hasMotionMimic();

    void initialize();
    
    int thinkingDelay();
    
    bool nextMotionSequenceNecessary(int closeness);
    
    motionSequenceKind determineNextMotionSequenceKind(int closeness);
    
    bool correctNextMotionSequenceKind();
};

#endif /* NGCustomMotionControl_h */
    
