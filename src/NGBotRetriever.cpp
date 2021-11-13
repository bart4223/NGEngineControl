//
//  NGBotRetriever.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.11.21.
//

#include "NGCommon.h"
#include "NGBotRetriever.h"

NGBotRetriever::NGBotRetriever() {
    _create();
}

void NGBotRetriever::_create() {
    
}

void NGBotRetriever::initialize() {
    
}

motionSequenceKind NGBotRetriever::determineNextMotionSequenceKind(int closeness) {
    switch(_lastKind) {
        case mskNone:
            _lastKind = mskStraight;
            break;
        case mskStraight:
            _lastKind = mskStop;
            _sequenceProcessed++;
            break;
        case mskStop:
            _lastKind = mskFullTurn;
            _sequenceProcessed++;
            break;
        case mskFullTurn:
            _lastKind = mskStraight;
            _sequenceProcessed++;
            break;
    }
    return _lastKind;
}

bool NGBotRetriever::correctNextMotionSequenceKind() {
    return false;
}

int NGBotRetriever::thinkingDelay() {
    return false;
}

bool NGBotRetriever::nextMotionSequenceNecessary(int closeness) {
    return _sequenceProcessed < 5;
}
