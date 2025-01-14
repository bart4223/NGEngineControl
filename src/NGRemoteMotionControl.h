//
//  NGRemoteMotionControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.10.22.
//

#ifndef NGRemoteMotionControl_h
#define NGRemoteMotionControl_h

#include <Arduino.h>
#include <NGCustomMotionControl.h>

class NGRemoteMotionControl : public NGCustomMotionControl {
 
private:
    int _lastMotionSequence = NOCURRENTMOTIONSEQUENCE;
    motionSequenceKind _lastMotionSequenceKind = mskNone;
    
protected:
    void _create(NGCustomSteeringControl *steeringControl);
    
    int _getMotionSequenceByKindUp(motionSequenceKind kind, int currentmotionSequence);

    int _getMotionSequenceByKindDown(motionSequenceKind kind, int currentmotionSequence);
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
