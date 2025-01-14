//
//  NGSimpleMotionControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 06.02.22.
//

#ifndef NGSimpleMotionControl_h
#define NGSimpleMotionControl_h

#include <Arduino.h>
#include <NGCustomMotionControl.h>

class NGSimpleMotionControl : public NGCustomMotionControl {
    
protected:
    void _create(NGCustomSteeringControl *steeringControl);
    
public:
    NGSimpleMotionControl(NGCustomSteeringControl *steeringControl);
    
    bool handleRemoteFunctionMenu(int currentmotionSequence);
    
    bool handleRemoteFunctionOK(int currentmotionSequence);
    
    bool handleRemoteFunctionPlay(int currentmotionSequence);

    bool handleRemoteFunctionUp(int currentmotionSequence);
    
    bool handleRemoteFunctionDown(int currentmotionSequence);
    
    bool handleRemoteFunctionLeft(int currentmotionSequence);
    
    bool handleRemoteFunctionRight(int currentmotionSequence);
};

#endif /* NGSimpleMotionControl_hp */
