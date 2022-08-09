//
//  NGSteeringControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 26.08.21.
//

#include "NGCommon.h"
#include "NGSteeringControl.h"

NGSteeringControl::NGSteeringControl() {    
    _create(ENGINE_0, ENGINE_1, DEFAULTSERIALRATE, ENGINENULLOFFSET, ENGINENULLOFFSET);
}

NGSteeringControl::NGSteeringControl(int engineLeft, int engineRight) {
    _create(engineLeft, engineRight, DEFAULTSERIALRATE, ENGINENULLOFFSET, ENGINENULLOFFSET);
}

NGSteeringControl::NGSteeringControl(int engineLeft, int engineRight, int offsetEngineLeft, int offsetEngineRight) {
    _create(engineLeft, engineRight, DEFAULTSERIALRATE, offsetEngineLeft, offsetEngineRight);
}

NGSteeringControl::NGSteeringControl(int engineLeft, int engineRight, int serialRate) {
    _create(engineLeft, engineRight, serialRate, ENGINENULLOFFSET, ENGINENULLOFFSET);
}

NGSteeringControl::NGSteeringControl(int engineLeft, int engineRight, int serialRate, int offsetEngineLeft, int offsetEngineRight) {
    _create(engineLeft, engineRight, serialRate, offsetEngineLeft, offsetEngineRight);
}

void NGSteeringControl::_create(int engineLeft, int engineRight, int serialRate, int offsetEngineLeft, int offsetEngineRight) {
    _initialized = false;
    _logging = true;
    _engineLeft = NGEngineControl(engineLeft, serialRate);
    _engineLeft.setLogging(_logging);
    _engineRight = NGEngineControl(engineRight, serialRate);
    _engineRight.setLogging(_logging);
    _offsetEngineLeft = offsetEngineLeft;
    _offsetEngineRight = offsetEngineRight;
}

byte NGSteeringControl::_calcEngineSpeed(byte speed, int offset) {
    byte res = speed;
    if (offset + res > MAXSPEED) {
        res = MAXSPEED;
    } else if (offset + res < NULLSPEED) {
        res = NULLSPEED;
    } else {
        res = offset + res;
    }
    return res;
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
    byte s = _calcEngineSpeed(_speed, _offsetEngineLeft);
    _engineLeft.setSpeed(s);
    s = _calcEngineSpeed(_speed, _offsetEngineRight);
    _engineRight.setSpeed(s);
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
    turnForward(turn, NULLSPEED);
}

void NGSteeringControl::turnForward(turnDirection turn, byte speed) {
    if (speed > NULLSPEED) {
        _speed = speed;
    }
    byte s = _calcEngineSpeed(_speed, _offsetEngineLeft);
    if (turn == tdLeftSoft) {
        _engineLeft.setSpeed(s / 2);
    } else if (turn == tdRightSoft) {
        _engineLeft.setSpeed(s * 1.16);
    } else {
        _engineLeft.setSpeed(s);
    }
    s = _calcEngineSpeed(_speed, _offsetEngineRight);
    if (turn == tdLeftSoft) {
        _engineRight.setSpeed(s * 1.16);
    } else if (turn == tdRightSoft) {
        _engineRight.setSpeed(s / 2);
    } else {
        _engineRight.setSpeed(s);
    }
    switch (turn) {
        case tdLeft:
        case tdLeftSoft:
            if (turn == tdLeftSoft) {
                _engineLeft.run(edForward);
            } else {
                _engineLeft.run(edBackward);
            }
            _engineRight.run(edForward);
            break;
        case tdRight:
        case tdRightSoft:
            _engineLeft.run(edForward);
            if (turn == tdRightSoft) {
                _engineRight.run(edForward);
            } else {
                _engineRight.run(edBackward);
            }
            break;
    }
}


void NGSteeringControl::turnBackward(turnDirection turn) {
    turnBackward(turn, NULLSPEED);
}

void NGSteeringControl::turnBackward(turnDirection turn, byte speed) {
    if (speed > NULLSPEED) {
        _speed = speed;
    }
    byte s = _calcEngineSpeed(_speed, _offsetEngineLeft);
    if (turn == tdLeftSoft) {
        _engineLeft.setSpeed(s / 2);
    } else if (turn == tdRightSoft) {
        _engineLeft.setSpeed(s * 1.16);
    } else {
        _engineLeft.setSpeed(s);
    }
    s = _calcEngineSpeed(_speed, _offsetEngineRight);
    if (turn == tdLeftSoft) {
        _engineRight.setSpeed(s * 1.16);
    } else if (turn == tdRightSoft) {
        _engineRight.setSpeed(s / 2);
    } else {
        _engineRight.setSpeed(s);
    }
    switch (turn) {
        case tdLeft:
        case tdLeftSoft:
            if (turn == tdLeftSoft) {
                _engineLeft.run(edBackward);
            } else {
                _engineLeft.run(edForward);
            }
            _engineRight.run(edBackward);
            break;
        case tdRight:
        case tdRightSoft:
            _engineLeft.run(edBackward);
            if (turn == tdRightSoft) {
                _engineRight.run(edBackward);
            } else {
                _engineRight.run(edForward);
            }
            break;
    }
}
