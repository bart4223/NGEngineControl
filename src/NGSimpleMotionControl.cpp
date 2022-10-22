//
//  NGSimpleMotionControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 06.02.22.
//

#include "NGSimpleMotionControl.h"

NGSimpleMotionControl::NGSimpleMotionControl(NGCustomSteeringControl *steeringControl) {
    _create(steeringControl);
}

void NGSimpleMotionControl::_create(NGCustomSteeringControl *steeringControl) {
    _steeringControl = steeringControl;
}

bool NGSimpleMotionControl::handleRemoteFunctionMenu(int currentmotionSequence) {
    return false;
}

bool NGSimpleMotionControl::handleRemoteFunctionOK(int currentmotionSequence) {
    return false;
}

bool NGSimpleMotionControl::handleRemoteFunctionPlay(int currentmotionSequence) {
    return false;
}

bool NGSimpleMotionControl::handleRemoteFunctionUp(int currentmotionSequence) {
    return false;
}

bool NGSimpleMotionControl::handleRemoteFunctionDown(int currentmotionSequence) {
    return false;
}

bool NGSimpleMotionControl::handleRemoteFunctionLeft(int currentmotionSequence) {
    return false;
}

bool NGSimpleMotionControl::handleRemoteFunctionRight(int currentmotionSequence) {
    return false;
}

