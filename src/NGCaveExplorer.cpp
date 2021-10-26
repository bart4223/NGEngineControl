//
//  NGCaveExplorer.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 21.10.21.
//

#include "NGCaveExplorer.h"

NGCaveExplorer::NGCaveExplorer() {
    _create();
}

void NGCaveExplorer::_create() {
    
}

void NGCaveExplorer::initialize() {
    NGCustomMotionMimic::initialize();
}

motionSequenceKind NGCaveExplorer::determineNextMotionSequence() {
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
