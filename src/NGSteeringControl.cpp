//
//  NGSteeringControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 26.08.21.
//

#include "NGCommon.h"
#include "NGSteeringControl.h"

NGSteeringControl::NGSteeringControl() {
    
}

NGSteeringControl::NGSteeringControl(int engineLeft, int engineRight) {
    _create(engineLeft, engineRight, DEFAULTSERIALRATE);
}

NGSteeringControl::NGSteeringControl(int engineLeft, int engineRight, int serialRate) {
    _create(engineLeft, engineRight, serialRate);
}

void NGSteeringControl::_create(int engineLeft, int engineRight, int serialRate) {
    _initialized = false;
    _logging = true;
    _engineLeft = NGEngineControl(engineLeft, serialRate);
    _engineLeft.setLogging(_logging);
    _engineRight = NGEngineControl(engineRight, serialRate);
    _engineRight.setLogging(_logging);
}

void NGSteeringControl::initialize() {
    char log[100];
    _engineLeft.initialize();
    _engineRight.initialize();
    _initialized = true;
    if (_logging) {
        sprintf(log, "Steering with engine %d and %d initialized", _engineLeft.getID(), _engineRight.getID());
        Serial.println(log);
    }
}

void NGSteeringControl::stop() {
    _engineLeft.stop();
    _engineRight.stop();
    if (_logging) {
        Serial.println("Engines stopped");
    }
}

void NGSteeringControl::runFullSpeedForward() {
    run(edForward, MAXSPEED);
}

void NGSteeringControl::runFullSpeedBackward() {
    run(edBackward, MAXSPEED);
}

void NGSteeringControl::run(engineDirection direction) {
    run(direction, NULLSPEED);
}

void NGSteeringControl::run(engineDirection direction, byte speed) {
    char log[100];
    if (speed > NULLSPEED) {
        _speed = speed;
    }
    _engineLeft.setSpeed(_speed);
    _engineRight.setSpeed(_speed);
    _engineLeft.run(direction);
    _engineRight.run(direction);
    if (_logging) {
        if (direction == edForward) {
            sprintf(log, "Engines runs with speed %d forward", _speed);
        } else {
            sprintf(log, "Engines runs with speed %d backward", _speed);
        }
        Serial.println(log);
    }
}

void NGSteeringControl::turnForward(turnDirection turn) {
    switch (turn) {
        case tdLeft:
            _engineLeft.setSpeed(_speed / 2);
            _engineRight.setSpeed(_speed);
            break;
        case tdRight:
            _engineLeft.setSpeed(_speed);
            _engineRight.setSpeed(_speed / 2);
            break;
    }
    _engineLeft.run(edForward);
    _engineRight.run(edForward);
}
