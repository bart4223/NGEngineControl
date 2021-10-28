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

motionSequenceKind NGCaveExplorer::determineNextMotionSequenceKind() {
    switch(_lastKind) {
        case mskNone:
        case mskLeft:
        case mskRight:
            _lastKind = mskStraight;
            break;
        case mskStraight:
            if (random(0, 2) == 0) {
                _lastKind = mskLeft;
            } else {
                _lastKind = mskRight;
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
