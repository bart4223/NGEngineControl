//
//  NGEngineControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 18.10.20.
//

#include "NGEngineControl.h"

NGEngineControl::NGEngineControl(int engine) {
    _create(engine,9600);
}

NGEngineControl::NGEngineControl(int engine, int serialRate) {
    _create(engine,serialRate);
}

void NGEngineControl::_create(int engine, int serialRate) {
    _initialized = false;
    _engine = engine;
    _serialRate = serialRate;
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
    char log[100];
    Serial.begin(_serialRate);
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
    char log[100];
    if (res) {
        sprintf(log,"Engine %d run...",_engine);
        Serial.println(log);
    } else {
        sprintf(log,"NGEngineControl with engine %d not initialized!",_engine);
        Serial.println(log);
    }
    return res;
}

bool NGEngineControl::stop() {
    bool res = _initialized;
    char log[100];
    if (res) {
        sprintf(log,"...Engine %d stopped",_engine);
        Serial.println(log);
    } else {
        sprintf(log,"NGEngineControl with engine %d not initialized!",_engine);
        Serial.println(log);
    }
    return res;
}
