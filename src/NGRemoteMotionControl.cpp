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
    int res = NOCURRENTMOTIONSEQUENCE;
    int first = NOCURRENTMOTIONSEQUENCE;
    for (int i = 0; i < _motionSequenceStorage->getSequenceCount(); i++) {
        if (_motionSequenceStorage->getSequenceKind(i) == kind) {
            if (first == NOCURRENTMOTIONSEQUENCE) {
                first = i;
            }
            if (i > currentmotionSequence) {
                res = i;
                break;
            }
        }
    }
    if (res == NOCURRENTMOTIONSEQUENCE && first != NOCURRENTMOTIONSEQUENCE) {
        res = first;
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
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionDown(int currentmotionSequence) {
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionLeft(int currentmotionSequence) {
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionRight(int currentmotionSequence) {
    return false;
}
