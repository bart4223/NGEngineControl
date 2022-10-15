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

bool NGRemoteMotionControl::handleRemoteFunctionMenu() {
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionOK() {
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionPlay() {
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionUp() {
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionDown() {
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionLeft() {
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionRight() {
    return false;
}
