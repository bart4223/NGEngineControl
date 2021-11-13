//
//  NGBotRetriever.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.11.21.
//

#ifndef NGBotRetriever_h
#define NGBotRetriever_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGCustomMotionMimic.h"

class NGBotRetriever : public NGCustomMotionMimic {
  
private:
    motionSequenceKind _lastKind = mskNone;
    int _sequenceProcessed = 0;
    
protected:
    void _create();
    
public:
    NGBotRetriever();
    
    void initialize();
    
    motionSequenceKind determineNextMotionSequenceKind(int closeness);
    
    bool nextMotionSequenceNecessary(int closeness);
    
    bool correctNextMotionSequenceKind();
    
    int thinkingDelay();
    
    void setBackwardCloseness(int closeness);
};

#endif /* NGBotRetriever_h */
