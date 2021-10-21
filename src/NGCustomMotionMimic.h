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

enum motionSequenceKind {mskNone, mskStraight, mskLeft, mskRight};

class NGCustomMotionMimic {
    
public:
    void initialize();
    
    virtual motionSequenceKind determineNextMotionSequence();
};

#endif /* NGCustomMotionMimic_h */
