//
//  NGEngineControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 18.10.20.
//

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
    }
    _speed = NULLSPEED;
    _interval = NULLINTERVAL;
    _direction = edNone;
    _running = false;
    _logging = true;
}

void NGEngineControl::initialize() {
    initialize(NULLSPEED);
}

void NGEngineControl::initialize(int speed) {
    char log[100];
    if (!_serialStarted) {
        Serial.begin(_serialRate);
        _serialStarted = true;
    }
    if (_logging) {
        sprintf(log, "Start initialization of NGEngineControl with engine %d...", _engine);
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
        case edForward:
            analogWrite(_backwardPin, NULLSPEED);
            dir = "forward";
            if (_interval > NULLINTERVAL) {
                for (int i = __startSpeed; i <= targetSpeed; i = i + STEPWIDTH) {
                    analogWrite(_forwardPin, i);
                    if (steps > NULLSTEPS) {
                        delay(_interval / steps);
                    }
                }
            }
            analogWrite(_forwardPin, targetSpeed);
            break;
        case edBackward:
            analogWrite(_forwardPin, NULLSPEED);
            dir = "backward";
            if (_interval > NULLINTERVAL) {
                for (int i = __startSpeed; i <= targetSpeed; i = i + STEPWIDTH) {
                    analogWrite(_backwardPin, i);
                    if (steps > NULLSTEPS) {
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
        sprintf(log, "NGEngineControl with engine %d not initialized!", _engine);
        Serial.println(log);
    }
    _direction = edNone;
    return res;
}

void NGEngineControl::_slowDown(int startSpeed, int targetSpeed, int interval) {
    char log[100];
    char* dir;
    if (interval > NULLINTERVAL) {
        int __targetSpeed = targetSpeed;
        if (__targetSpeed < MINSPEED) {
            __targetSpeed = MINSPEED;
        }
        int steps = (startSpeed - __targetSpeed) / STEPWIDTH;
        switch(_direction) {
            case edForward:
                dir = "forward";
                for (int i = startSpeed; i >= __targetSpeed; i = i - STEPWIDTH) {
                    analogWrite(_forwardPin, i);
                    if (steps > NULLSTEPS) {
                        delay(interval / steps);
                    }
                }
                if (targetSpeed != NULLSPEED) {
                    analogWrite(_forwardPin, targetSpeed);
                }
                break;
            case edBackward:
                dir = "backward";
                for (int i = startSpeed; i >= __targetSpeed; i = i - STEPWIDTH) {
                    analogWrite(_backwardPin, i);
                    if (steps > NULLSTEPS) {
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
