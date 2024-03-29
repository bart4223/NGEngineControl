//
//  NGEngineControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 18.10.20.
//

#include "NGCommon.h"
#include "NGEngineControl.h"

NGEngineControl::NGEngineControl() {
    
}

NGEngineControl::NGEngineControl(int engine) {
    _create(engine, DEFAULTSERIALRATE);
}

NGEngineControl::NGEngineControl(int engine, int serialRate) {
    _create(engine, serialRate);
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
        case ENGINE_1:
            _forwardPin = ENGINE_1_FORWARD;
            _backwardPin = ENGINE_1_BACKWARD;
            break;
        case ENGINE_2:
            _forwardPin = ENGINE_2_FORWARD;
            _backwardPin = ENGINE_2_BACKWARD;
            break;
        case ENGINE_3:
            _forwardPin = ENGINE_3_FORWARD;
            _backwardPin = ENGINE_3_BACKWARD;
            break;
    }
    _speed = NULLSPEED;
    _interval = NULLINTERVAL;
    _direction = edNone;
    _running = false;
    _logging = true;
}

void NGEngineControl::_setSpeed(int pin, int speed) {
    if (_engine == ENGINE_3) {
        if (speed < MAXSPEED / 2 + 1) {
            digitalWrite(pin, LOW);
        } else {
            digitalWrite(pin, HIGH);
        }
    } else {
        analogWrite(pin, speed);
    }
}

void NGEngineControl::initialize() {
    initialize(NULLSPEED);
}

void NGEngineControl::initialize(int speed) {
    char log[100];
    _ensureGlobalSerial(_serialRate);
    pinMode(_forwardPin, OUTPUT);
    pinMode(_backwardPin, OUTPUT);
    _speed = speed;
    _initialized = true;
    if (_logging) {
        sprintf(log, "Engine %d initialized", _engine);
        Serial.println(log);
    }
}

int NGEngineControl::getID() {
    return _engine;
}

int NGEngineControl::getSpeed() {
    return _speed;
}

void NGEngineControl::setLogging(bool logging) {
    _logging = logging;
}

void NGEngineControl::setSpeed(int speed) {
    setSpeed(speed, NULLINTERVAL);
}

void NGEngineControl::setSpeed(int speed, int interval) {
    int oldspeed = _speed;
    _speed = speed;
    if (_speed > MAXSPEED) {
        _speed = MAXSPEED;
    } else if (_speed < MINSPEED) {
        _speed = MINSPEED;
    }
    _interval = interval;
    if (_speed > NULLSPEED) {
        if (_running) {
            if (oldspeed < _speed) {
                _speedUp(oldspeed, _speed);
            } else if (oldspeed > _speed) {
                _slowDown(oldspeed, _speed, interval);
            }
            _running = true;
        }
    } else if (_running) {
        _slowDown(_speed, NULLSPEED, interval);
        _running = false;
        _interval = NULLINTERVAL;
    }
}

bool NGEngineControl::run(engineDirection direction) {
    bool res = _initialized;
    char log[100];
    _direction = direction;
    if (res) {
        if (direction != edNone && _speed > NULLSPEED) {
            _speedUp(MINSPEED, _speed);
            _running = true;
        }
    } else if (_logging) {
        sprintf(log, "Engine %d not initialized!", _engine);
        Serial.println(log);
    }
    return res;
}

void NGEngineControl::_speedUp(int startSpeed, int targetSpeed) {
    char log[100];
    char* dir;
    int __startSpeed = startSpeed;
    if (__startSpeed < MINSPEED) {
        __startSpeed = MINSPEED;
    }
    int steps = (targetSpeed - __startSpeed) / STEPWIDTH;
    switch (_direction) {
        case edForward:
            _setSpeed(_backwardPin, NULLSPEED);
            dir = (char*)"forward";
            if (_interval > NULLINTERVAL) {
                for (int i = __startSpeed; i <= targetSpeed; i = i + STEPWIDTH) {
                    _setSpeed(_forwardPin, i);
                    if (steps > NULLSTEPS) {
                        delay(_interval / steps);
                    }
                }
            }
            _setSpeed(_forwardPin, targetSpeed);
            break;
        case edBackward:
            _setSpeed(_forwardPin, NULLSPEED);
            dir = (char*)"backward";
            if (_interval > NULLINTERVAL) {
                for (int i = __startSpeed; i <= targetSpeed; i = i + STEPWIDTH) {
                    _setSpeed(_backwardPin, i);
                    if (steps > NULLSTEPS) {
                        delay(_interval / steps);
                    }
                }
            }
            _setSpeed(_backwardPin, targetSpeed);
            break;
    }
    if (_logging) {
        sprintf(log, "Engine %d speed %d %s...", _engine, targetSpeed, dir);
        Serial.println(log);
    }
}

bool NGEngineControl::stop() {
    stop(NULLINTERVAL);
}
    
bool NGEngineControl::stop(int interval) {
    bool res = _initialized;
    char log[100];
    int __interval = interval;
    if (__interval == NULLINTERVAL) {
        __interval = _interval;
    }
    if (res) {
        if (_direction != edNone) {
            _slowDown(_speed, NULLSPEED, __interval);
            _running = false;
        }
    } else if (_logging) {
        sprintf(log, "Engine %d not initialized!", _engine);
        Serial.println(log);
    }
    _direction = edNone;
    return res;
}

void NGEngineControl::_slowDown(int startSpeed, int targetSpeed, int interval) {
    char log[100];
    char* dir;
    if (_direction == edForward) {
        dir = (char*)"forward";
    } else {
        dir = (char*)"backward";
    }
    if (interval > NULLINTERVAL) {
        int __targetSpeed = targetSpeed;
        if (__targetSpeed < MINSPEED) {
            __targetSpeed = MINSPEED;
        }
        int steps = (startSpeed - __targetSpeed) / STEPWIDTH;
        switch(_direction) {
            case edForward:
                for (int i = startSpeed; i >= __targetSpeed; i = i - STEPWIDTH) {
                    _setSpeed(_forwardPin, i);
                    if (steps > NULLSTEPS) {
                        delay(interval / steps);
                    }
                }
                if (targetSpeed != NULLSPEED) {
                    _setSpeed(_forwardPin, targetSpeed);
                }
                break;
            case edBackward:               
                for (int i = startSpeed; i >= __targetSpeed; i = i - STEPWIDTH) {
                    _setSpeed(_backwardPin, i);
                    if (steps > NULLSTEPS) {
                        delay(interval / steps);
                    }
                }
                if (targetSpeed != NULLSPEED) {
                    _setSpeed(_backwardPin, targetSpeed);
                }
                break;
        }
    }
    if (targetSpeed == NULLSPEED) {
        _setSpeed(_forwardPin, targetSpeed);
        _setSpeed(_backwardPin, targetSpeed);
        sprintf(log, "...Engine %d stopped", _engine);
    } else {
        sprintf(log, "Engine %d speed %d %s...", _engine, targetSpeed, dir);
    }
    if (_logging) {
        Serial.println(log);
    }
}

bool NGEngineControl::isRunning() {
    return _running;
}
