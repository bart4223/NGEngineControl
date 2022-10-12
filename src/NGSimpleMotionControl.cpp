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

bool NGSimpleMotionControl::handleRemoteFunctionMenu() {
    return false;
}

bool NGSimpleMotionControl::handleRemoteFunctionOK() {
    return false;
}

bool NGSimpleMotionControl::handleRemoteFunctionPlay() {
    return false;
}

bool NGSimpleMotionControl::handleRemoteFunctionUp() {
    return false;
}

bool NGSimpleMotionControl::handleRemoteFunctionDown() {
    return false;
}

bool NGSimpleMotionControl::handleRemoteFunctionLeft() {
    return false;
}

bool NGSimpleMotionControl::handleRemoteFunctionRight() {
    return false;
}

