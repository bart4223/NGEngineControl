//
//  NGEngineControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 18.10.20.
//

#include "NGEngineControl.h"

NGEngineControl::NGEngineControl(int forwardPin, int backwardPin) {
    _initialized = false;
    _forwardPin = forwardPin;
    _backwardPin = backwardPin;
    _speed = 0;
}

void NGEngineControl::initialize() {
    Serial.begin(9600);
    _initialized = true;
    Serial.print("NGEngineControl successfully initialized");
}

void NGEngineControl::setSpeed(int speed) {
    _speed = speed;
}

bool NGEngineControl::run(direction direction) {
    bool res = _initialized;
    if (res) {
        
    } else {
        Serial.print("NGEngineControl not initialized!");
    }
    return res;
}
