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
    motionSequenceKind kind = _lastKind;
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
            }
            break;
        case mskStraight:
            if (closeness >= 0 && closeness < _backwardCloseness) {
                _lastKind = mskBack;
            } else if (getYesOrNo()) {
                _lastKind = mskLeft;
            } else {
                _lastKind = mskRight;
            }
            break;
        case mskBack:
            if (closeness == NONECONTACT) {
                if (getYesOrNo()) {
                    _lastKind = mskLeft;
                } else {
                    _lastKind = mskRight;
                }
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
