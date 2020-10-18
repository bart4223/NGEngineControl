//
//  NGEngineControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 18.10.20.
//

#include "NGEngineControl.h"

NGEngineControl::NGEngineControl(int engine) {
    _initialized = false;
    _engine = engine;
    switch (_engine) {
        case ENGINE_0:
            _forwardPin = ENGINE_0_FORWARD;
            _backwardPin = ENGINE_0_BACKWARD;
            break;
        default:
            break;
    }
    _speed = 0;
}

void NGEngineControl::initialize() {
    Serial.begin(9600);
    char log[100];
    sprintf(log,"Start initialzation of NGEngineControl with engine %d...",_engine);
    Serial.println(log);
    _initialized = true;
    sprintf(log,"...NGEngineControl with engine %d successfully initialized",_engine);
    Serial.println(log);
}

void NGEngineControl::setSpeed(int speed) {
    _speed = speed;
}

bool NGEngineControl::run(direction direction) {
    bool res = _initialized;
    if (res) {
        
    } else {
        char log[100];
        sprintf(log,"NGEngineControl with engine %d not initialized!",_engine);
        Serial.println(log);
    }
    return res;
}
