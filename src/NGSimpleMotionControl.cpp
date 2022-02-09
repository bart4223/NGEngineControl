//
//  NGSimpleMotionControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 06.02.22.
//

#include "NGSimpleMotionControl.h"

NGSimpleMotionControl::NGSimpleMotionControl(NGSteeringControl *steeringControl) {
    _create(steeringControl);
}

void NGSimpleMotionControl::_create(NGSteeringControl *steeringControl) {
    _steeringControl = steeringControl;
}
