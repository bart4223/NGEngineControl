//
//  NGEngineControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 18.10.20.
//

#include "NGEngineControl.h"

NGEngineControl::NGEngineControl(int engine) {
    _create(engine, 9600);
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
    }
    _speed = NULLSPEED;
    _interval = 0;
    _direction = NONE;
    _running = false;
    _logging = true;
}

void NGEngineControl::initialize() {
    initialize(0);
}

void NGEngineControl::initialize(int speed) {
    char log[100];
    Serial.begin(_serialRate);
    if (_logging) {
        sprintf(log, "Start initialzation of NGEngineControl with engine %d...", _engine);
        Serial.println(log);
    }
    pinMode(_forwardPin, OUTPUT);
    pinMode(_backwardPin, OUTPUT);
    _speed = speed;
    _initialized = true;
    if (_logging) {
        sprintf(log, "...NGEngineControl with engine %d successfully initialized", _engine);
        Serial.println(log);
    }
}

void NGEngineControl::setLogging(bool logging) {
    _logging = logging;
}

void NGEngineControl::setSpeed(int speed) {
    setSpeed(speed, 0);
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
        _interval = 0;
    }
}

bool NGEngineControl::run(direction direction) {
    bool res = _initialized;
    char log[100];
    _direction = direction;
    if (res) {
        if (direction != NONE && _speed > NULLSPEED) {
            _speedUp(MINSPEED, _speed);
            _running = true;
        }
    } else if (_logging) {
        sprintf(log, "NGEngineControl with engine %d not initialized!", _engine);
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
        case FORWARD:
            analogWrite(_backwardPin, NULLSPEED);
            dir = "forward";
            if (_interval > 0) {
                for (int i = __startSpeed; i <= targetSpeed; i = i + STEPWIDTH) {
                    analogWrite(_forwardPin, i);
                    if (steps > 0) {
                        delay(_interval / steps);
                    }
                }
            }
            analogWrite(_forwardPin, targetSpeed);
            break;
        case BACKWARD:
            analogWrite(_forwardPin, NULLSPEED);
            dir = "backward";
            if (_interval > 0) {
                for (int i = __startSpeed; i <= targetSpeed; i = i + STEPWIDTH) {
                    analogWrite(_backwardPin, i);
                    if (steps > 0) {
                        delay(_interval / steps);
                    }
                }
            }
            analogWrite(_backwardPin, targetSpeed);
            break;
    }
    if (_logging) {
        sprintf(log, "Engine %d now run with speed %d %s...", _engine, targetSpeed, dir);
        Serial.println(log);
    }
}

bool NGEngineControl::stop() {
    stop(0);
}
    
bool NGEngineControl::stop(int interval) {
    bool res = _initialized;
    char log[100];
    int __interval = interval;
    if (__interval == 0) {
        __interval = _interval;
    }
    if (res) {
        if (_direction != NONE) {
            _slowDown(_speed, NULLSPEED, __interval);
            _running = false;
        }
    } else if (_logging) {
        sprintf(log, "NGEngineControl with engine %d not initialized!", _engine);
        Serial.println(log);
    }
    _direction = NONE;
    return res;
}

void NGEngineControl::_slowDown(int startSpeed, int targetSpeed, int interval) {
    char log[100];
    char* dir;
    if (interval > 0) {
        int __targetSpeed = targetSpeed;
        if (__targetSpeed < MINSPEED) {
            __targetSpeed = MINSPEED;
        }
        int steps = (startSpeed - __targetSpeed) / STEPWIDTH;
        switch(_direction) {
            case FORWARD:
                dir = "forward";
                for (int i = startSpeed; i >= __targetSpeed; i = i - STEPWIDTH) {
                    analogWrite(_forwardPin, i);
                    if (steps > 0) {
                        delay(interval / steps);
                    }
                }
                if (targetSpeed != NULLSPEED) {
                    analogWrite(_forwardPin, targetSpeed);
                }
                break;
            case BACKWARD:
                dir = "backward";
                for (int i = startSpeed; i >= __targetSpeed; i = i - STEPWIDTH) {
                    analogWrite(_backwardPin, i);
                    if (steps > 0) {
                        delay(interval / steps);
                    }
                }
                if (targetSpeed != NULLSPEED) {
                    analogWrite(_backwardPin, targetSpeed);
                }
                break;
        }
    }
    if (targetSpeed == NULLSPEED) {
        analogWrite(_forwardPin, targetSpeed);
        analogWrite(_backwardPin, targetSpeed);
        sprintf(log, "...Engine %d stopped", _engine);
    } else {
        sprintf(log, "Engine %d now run with speed %d %s...", _engine, targetSpeed, dir);
    }
    if (_logging) {
        Serial.println(log);
    }
}
