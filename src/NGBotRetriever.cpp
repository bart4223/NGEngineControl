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
            if (closeness != NONECONTACT) {
                _lastKind = mskRight;
                _avoid = true;
            } else {
                _avoid = false;
            }
            break;
        case mskRight:
            _lastKind = mskStraight;
            _avoid = false;
            break;
    }
    return _lastKind;
}

bool NGBotRetriever::correctNextMotionSequenceKind() {
    return false;
}

int NGBotRetriever::thinkingDelay() {
    return 0;
}

bool NGBotRetriever::nextMotionSequenceNecessary(int closeness) {
    return !_avoid || closeness == 0;
}
