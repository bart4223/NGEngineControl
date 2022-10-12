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
    Serial.println("Menu");
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionOK() {
    Serial.println("OK");
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionPlay() {
    Serial.println("Play");
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionUp() {
    Serial.println("Up");
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionDown() {
    Serial.println("Down");
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionLeft() {
    Serial.println("Left");
    return false;
}

bool NGRemoteMotionControl::handleRemoteFunctionRight() {
    Serial.println("Right");
    return false;
}
