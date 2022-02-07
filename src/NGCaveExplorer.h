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

#define DEFBACKWARDCLOSENESS 5

class NGCaveExplorer : public NGCustomMotionMimic {
  
private:
    motionSequenceKind _lastKind = mskNone;
    int _backwardCloseness = DEFBACKWARDCLOSENESS;
    bool _avoid = false;
    
protected:
    void _create();
    
public:
    NGCaveExplorer();
    
    void initialize();
    
    motionSequenceKind determineNextMotionSequenceKind(int closeness);
    
    bool nextMotionSequenceNecessary(int closeness);
    
    bool correctNextMotionSequenceKind();
    
    int thinkingDelay();
    
    char* getName();
    
    void setBackwardCloseness(int closeness);
};

#endif /* NGCaveExplorer_h */
