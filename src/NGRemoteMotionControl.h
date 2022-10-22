//
//  NGRemoteMotionControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.10.22.
//

#ifndef NGRemoteMotionControl_h
#define NGRemoteMotionControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomMotionControl.h>

class NGRemoteMotionControl : public NGCustomMotionControl {
  
protected:
    void _create(NGCustomSteeringControl *steeringControl);
    
    int _getMotionSequenceByKind(motionSequenceKind kind, int currentmotionSequence);
public:
    NGRemoteMotionControl(NGCustomSteeringControl *steeringControl);
    
    bool handleRemoteFunctionMenu(int currentmotionSequence);
    
    bool handleRemoteFunctionOK(int currentmotionSequence);
    
    bool handleRemoteFunctionPlay(int currentmotionSequence);

    bool handleRemoteFunctionUp(int currentmotionSequence);
    
    bool handleRemoteFunctionDown(int currentmotionSequence);
    
    bool handleRemoteFunctionLeft(int currentmotionSequence);
    
    bool handleRemoteFunctionRight(int currentmotionSequence);
};

#endif /* NGRemoteMotionControl_h */
