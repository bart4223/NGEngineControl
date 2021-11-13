//
//  NGCaveExplorer.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 21.10.21.
//

#include "NGCommon.h"
#include "NGCaveExplorer.h"

NGCaveExplorer::NGCaveExplorer() {
    _create();
}

void NGCaveExplorer::_create() {
    
}

void NGCaveExplorer::initialize() {
    
}

motionSequenceKind NGCaveExplorer::determineNextMotionSequenceKind(int closeness) {
    switch(_lastKind) {
        case mskNone:
            _lastKind = mskStraight;
            break;
        case mskLeft:
        case mskRight:
            if (closeness >= 0 && closeness < _backwardCloseness) {
                _lastKind = mskBack;
            } else if (closeness == NONECONTACT) {
                _lastKind = mskStraight;
                _avoid = false;
            }
            break;
        case mskStraight:
            if (closeness >= 0 && closeness < _backwardCloseness) {
                _lastKind = mskBack;
            } else if (getYesOrNo()) {
                _lastKind = mskLeft;
                _avoid = true;
            } else {
                _lastKind = mskRight;
                _avoid = true;
            }
            break;
        case mskBack:
            if (closeness == NONECONTACT) {
                if (getYesOrNo()) {
                    _lastKind = mskLeft;
                } else {
                    _lastKind = mskRight;
                }
                _avoid = false;
            }
            break;
    }
    return _lastKind;
}

bool NGCaveExplorer::correctNextMotionSequenceKind() {
    return getYesOrNo();
}

int NGCaveExplorer::thinkingDelay() {
    return random(0, 4);
}

void NGCaveExplorer::setBackwardCloseness(int closeness) {
    _backwardCloseness = closeness;
}

bool NGCaveExplorer::nextMotionSequenceNecessary(int closeness) {
    return !_avoid || closeness == 0;
}
