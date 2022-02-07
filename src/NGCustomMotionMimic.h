//
//  NGCustomMotionMimic.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 19.10.21.
//

#ifndef NGCustomMotionMimic_h
#define NGCustomMotionMimic_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define NONECONTACT -1

enum motionSequenceKind {mskNone, mskStraight, mskLeft, mskRight, mskStop, mskBack, mskFullTurn};

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
