//
//  NGBotRetriever.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.11.21.
//

#ifndef NGBotRetriever_h
#define NGBotRetriever_h

#include <Arduino.h>
#include <NGCustomMotionMimic.h>

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
    
    char* getName();
    
    void setBackwardCloseness(int closeness);
};

#endif /* NGBotRetriever_h */
