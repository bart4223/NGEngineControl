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
    Serial.println("Start initialzation of NGEngineControl...");
    _initialized = true;
    Serial.println("...NGEngineControl successfully initialized");
}

void NGEngineControl::setSpeed(int speed) {
    _speed = speed;
}

bool NGEngineControl::run(direction direction) {
    bool res = _initialized;
    if (res) {
        
    } else {
        Serial.println("NGEngineControl not initialized!");
    }
    return res;
}
