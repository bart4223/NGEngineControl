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
    _Speed = 0;
}

void setSpeed(int Speed) {
    _Speed = Speed;
}

void Run() {
    
}
