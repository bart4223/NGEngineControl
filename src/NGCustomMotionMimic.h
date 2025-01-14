//
//  NGCustomMotionMimic.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 19.10.21.
//

#ifndef NGCustomMotionMimic_h
#define NGCustomMotionMimic_h

#include <Arduino.h>
#include <NGMotionSequenceStorage.h>

#define NONECONTACT -1

class NGCustomMotionMimic {
    
public:
    virtual void initialize();
    
    virtual motionSequenceKind determineNextMotionSequenceKind(int closeness);
    
    virtual bool nextMotionSequenceNecessary(int closeness);
    
    virtual bool correctNextMotionSequenceKind();
    
    virtual int thinkingDelay();
    
    virtual char* getName();
};

#endif /* NGCustomMotionMimic_h */
