//
//  NGSimpleMotionMimic.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 03.06.23.
//

#ifndef NGSimpleMotionMimic_h
#define NGSimpleMotionMimic_h

#include <Arduino.h>
#include <NGCustomMotionMimic.h>

class NGSimpleMotionMimic : public NGCustomMotionMimic {
  
protected:
    void _create();
    
public:
    NGSimpleMotionMimic();
    
    void initialize();
    
    motionSequenceKind determineNextMotionSequenceKind(int closeness);
    
    bool nextMotionSequenceNecessary(int closeness);
    
    bool correctNextMotionSequenceKind();
    
    int thinkingDelay();
    
    char* getName();
};

#endif /* NGSimpleMotionMimic_h */
