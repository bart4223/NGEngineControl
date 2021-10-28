//
//  NGCaveExplorer.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 21.10.21.
//

#ifndef NGCaveExplorer_h
#define NGCaveExplorer_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGCustomMotionMimic.h"

class NGCaveExplorer : public NGCustomMotionMimic {
  
private:
    motionSequenceKind _lastKind = mskNone;
    
protected:
    void _create();
    
public:
    NGCaveExplorer();
    
    void initialize();
    
    motionSequenceKind determineNextMotionSequenceKind();
    
    bool correctNextMotionSequenceKind();
    
    int thinkingDelay();
};

#endif /* NGCaveExplorer_h */
