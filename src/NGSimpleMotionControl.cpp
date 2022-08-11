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
