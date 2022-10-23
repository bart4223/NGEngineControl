//
//  NGRemoteMotionControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.10.22.
//

#include "NGRemoteMotionControl.h"

NGRemoteMotionControl::NGRemoteMotionControl(NGCustomSteeringControl *steeringControl) {
    _create(steeringControl);
}

void NGRemoteMotionControl::_create(NGCustomSteeringControl *steeringControl) {
    _steeringControl = steeringControl;
}

int NGRemoteMotionControl::_getMotionSequenceByKind(motionSequenceKind kind, int currentmotionSequence) {
    int res = currentmotionSequence;
    for (int i = 0; i < _motionSequenceStorage->getSequenceCount(); i++) {
        if (_motionSequenceStorage->getSequenceKind(i) == kind) {
            if (i > res) {
                res = i;
                break;
            }
        }
    }
    return res;
}

bool NGRemoteMotionControl::handleRemoteFunctionMenu(int currentmotionSequence) {
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionOK(int currentmotionSequence) {
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionPlay(int currentmotionSequence) {
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionUp(int currentmotionSequence) {
    _nextMotionSequence = _getMotionSequenceByKind(mskStraight, currentmotionSequence);
    return true;
}

bool NGRemoteMotionControl::handleRemoteFunctionDown(int currentmotionSequence) {
    _nextMotionSequence = _getMotionSequenceByKind(mskBack, currentmotionSequence);
    return true;
}

bool NGRemoteMotionControl::handleRemoteFunctionLeft(int currentmotionSequence) {
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionRight(int currentmotionSequence) {
    return false;
}
