//
//  NGEngineControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 18.10.20.
//

#include "NGEngineControl.h"

NGEngineControl::NGEngineControl(int forwardPin, int backwardPin) {
    _forwardPin = forwardPin;
    _backwardPin = backwardPin;
    _speed = 0;
}

void NGEngineControl::setSpeed(int speed) {
    _speed = speed;
}

void NGEngineControl::run(direction direction) {
    
}
