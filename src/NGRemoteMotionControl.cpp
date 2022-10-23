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

int NGRemoteMotionControl::_getMotionSequenceByKindUp(motionSequenceKind kind, int currentmotionSequence) {
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

int NGRemoteMotionControl::_getMotionSequenceByKindDown(motionSequenceKind kind, int currentmotionSequence) {
    int res = currentmotionSequence;
    for (int i = _motionSequenceStorage->getSequenceCount() - 1; i >= 0 ; i--) {
        if (_motionSequenceStorage->getSequenceKind(i) == kind) {
            if (i < res) {
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
    switch(_lastMotionSequenceKind) {
        case mskNone:
        case mskStop:
        case mskStraight:
            _nextMotionSequence = _getMotionSequenceByKindUp(mskStraight, _lastMotionSequence);
            if (_nextMotionSequence != NOCURRENTMOTIONSEQUENCE) {
                _lastMotionSequenceKind = mskStraight;
                _lastMotionSequence = _nextMotionSequence;
            }
            break;
        case mskBack:
            _nextMotionSequence = _getMotionSequenceByKindDown(mskBack, _lastMotionSequence);
            if (_nextMotionSequence != NOCURRENTMOTIONSEQUENCE) {
                if (_nextMotionSequence != currentmotionSequence) {
                    _lastMotionSequenceKind = mskBack;
                    _lastMotionSequence = _nextMotionSequence;
                } else {
                    _nextMotionSequence = _getMotionSequenceByKindUp(mskStop, NOCURRENTMOTIONSEQUENCE);
                    _lastMotionSequenceKind = mskStop;
                    _lastMotionSequence = NOCURRENTMOTIONSEQUENCE;
                }
            }
            break;
    }
    return true;
}

bool NGRemoteMotionControl::handleRemoteFunctionDown(int currentmotionSequence) {
    switch(_lastMotionSequenceKind) {
        case mskNone:
        case mskStop:
        case mskBack:
            _nextMotionSequence = _getMotionSequenceByKindUp(mskBack, _lastMotionSequence);
            if (_nextMotionSequence != NOCURRENTMOTIONSEQUENCE) {
                _lastMotionSequenceKind = mskBack;
                _lastMotionSequence = _nextMotionSequence;
            }
            break;
        case mskStraight:
            _nextMotionSequence = _getMotionSequenceByKindDown(mskStraight, _lastMotionSequence);
            if (_nextMotionSequence != NOCURRENTMOTIONSEQUENCE) {
                if (_nextMotionSequence != currentmotionSequence) {
                    _lastMotionSequenceKind = mskStraight;
                    _lastMotionSequence = _nextMotionSequence;
                } else {
                    _nextMotionSequence = _getMotionSequenceByKindUp(mskStop, NOCURRENTMOTIONSEQUENCE);
                    _lastMotionSequenceKind = mskStop;
                    _lastMotionSequence = NOCURRENTMOTIONSEQUENCE;
                }
            }
            break;
    }
    return true;
}

bool NGRemoteMotionControl::handleRemoteFunctionLeft(int currentmotionSequence) {
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionRight(int currentmotionSequence) {
    return false;
}
