//
//  NGVoidMotionMimic.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 06.02.22.
//

#ifndef NGVoidMotionMimic_h
#define NGVoidMotionMimic_h

#include <Arduino.h>
#include <NGCustomMotionMimic.h>

class NGVoidMotionMimic : public NGCustomMotionMimic {
  
protected:
    void _create();
    
public:
    NGVoidMotionMimic();
    
    void initialize();
    
    motionSequenceKind determineNextMotionSequenceKind(int closeness);
    
    bool nextMotionSequenceNecessary(int closeness);
    
    bool correctNextMotionSequenceKind();
    
    int thinkingDelay();
    
    char* getName();    
};

#endif /* NGVoidMotionMimic_h */
