//
//  NGJoystickControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 13.08.22.
//

#include "NGJoystickControl.h"

NGJoystickControl::NGJoystickControl() {
    _create(jkAnalog, NOJOYSTICKID, DEFJOYSTICKPINX, DEFJOYSTICKPINY, 0, 0, DEFJOYSTICKPINFIRE, false);
}

NGJoystickControl::NGJoystickControl(int id) {
    _create(jkAnalog, id, DEFJOYSTICKPINX, DEFJOYSTICKPINY, 0, 0, DEFJOYSTICKPINFIRE, false);
}

NGJoystickControl::NGJoystickControl(byte joystickPinX, byte joystickPinY, byte joystickPinFire) {
    _create(jkAnalog, NOJOYSTICKID, joystickPinX, joystickPinY, 0, 0, joystickPinFire, false);
}

NGJoystickControl::NGJoystickControl(int id, byte joystickPinX, byte joystickPinY, byte joystickPinFire) {
    _create(jkAnalog, id, joystickPinX, joystickPinY, 0, 0, joystickPinFire, false);
}

NGJoystickControl::NGJoystickControl(int id, byte joystickPinXL, byte joystickPinXR, byte joystickPinYD, byte joystickPinYU, byte joystickPinFire) {
    _create(jkDigital, id, joystickPinXL, joystickPinYD, joystickPinXR, joystickPinYU, joystickPinFire, false);
}

NGJoystickControl::NGJoystickControl(int id, byte joystickPinXL, byte joystickPinXR, byte joystickPinYD, byte joystickPinYU, byte joystickPinFire, bool joystickPinFireHigh) {
    _create(jkDigital, id, joystickPinXL, joystickPinYD, joystickPinXR, joystickPinYU, joystickPinFire, joystickPinFireHigh);
}

void NGJoystickControl::_create(joystickKind kind, int id, byte joystickPinX, byte joystickPinY, byte joystickPinX2, byte joystickPinY2, byte joystickPinFire, bool joystickPinFireHigh) {
    _kind = kind;
    _id = id;
    switch(_kind) {
        case jkAnalog:
            _joystickPinX = joystickPinX;
            _joystickPinY = joystickPinY;
            break;
        case jkDigital:
            _joystickPinX = joystickPinX;
            _joystickPinY = joystickPinY;
            _joystickPinX2 = joystickPinX2;
            _joystickPinY2 = joystickPinY2;
            break;
    }
    _joystickPinFire = joystickPinFire;
    _joystickPinFireHigh = joystickPinFireHigh;
}

void NGJoystickControl::initialize() {
    if (_kind == jkDigital) {
        pinMode(_joystickPinX, INPUT_PULLUP);
        pinMode(_joystickPinX2, INPUT_PULLUP);
        pinMode(_joystickPinY, INPUT_PULLUP);
        pinMode(_joystickPinY2, INPUT_PULLUP);
    }
    if (_joystickPinFireHigh) {
        pinMode(_joystickPinFire, INPUT);
    } else {
        pinMode(_joystickPinFire, INPUT_PULLUP);
    }
    pinMode(_joystickPinFire, INPUT);
    for (int i = 0; i < _joystickActionCount; i++) {
        if (_joystickActions[i].pin != NOJOYSTICKACTIONPIN) {
            pinMode(_joystickActions[i].pin, OUTPUT);
        }
        switch(_joystickActions[i].mode) {
            case jamTriggerLOW:
                digitalWrite(_joystickActions[i].pin, HIGH);
                break;
            case jamTriggerHIGH:
                digitalWrite(_joystickActions[i].pin, LOW);
                break;
        }
    }
}

void NGJoystickControl::setLogging(bool logging) {
    _logging = logging;
}

bool NGJoystickControl::getLogging() {
    return _logging;
}

void NGJoystickControl::setLogXAxis(bool logging) {
    _logXAxis = logging;
}

void NGJoystickControl::setLogYAxis(bool logging) {
    _logYAxis = logging;
}

void NGJoystickControl::setContinuousFireThreshold(int continuousfirethreshold) {
    _continuousFireThreshold = continuousfirethreshold;
}

void NGJoystickControl::registerActionCallback(joystickActionCallbackFunc callback) {
    _actionCallback = callback;
}

void NGJoystickControl::registerActionValueCallback(joystickActionValueCallbackFunc callback) {
    _actionValueCallback = callback;
}

void NGJoystickControl::registerAction(joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, int delay, joystickMovement movement) {
    registerAction(NOJOYSTICKACTIONPIN, mode, axis, kind, threshold, delay, movement);
}

void NGJoystickControl::registerAction(joystickAxis axis, joystickThresholdKind kind, int threshold, int delay, joystickMovement movement) {
    registerAction(NOJOYSTICKACTIONPIN, jamNone, axis, kind, threshold, delay, movement);
}

void NGJoystickControl::registerAction(int pin, joystickActionMode mode, joystickMovement movement) {
    registerAction(pin, mode, NOJOYSTICKDELAY, movement);
}

void NGJoystickControl::registerAction(int delay, joystickMovement movement) {
    registerAction(NOJOYSTICKACTIONPIN, jamNone, delay, movement);
}

void NGJoystickControl::registerAction(int pin, joystickActionMode mode, int delay, joystickMovement movement) {
    registerAction(pin, mode, jaNone, jtkNone, NOJOYSTICKTHRESHOLD, delay, movement);
}

void NGJoystickControl::registerAction(int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, joystickMovement movement) {
    registerAction(pin, mode, axis, kind, threshold, NOJOYSTICKDELAY, movement);
}

void NGJoystickControl::registerAction(int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, int delay, joystickMovement movement) {
    registerAction(pin, mode, axis, kind, threshold, delay, movement, DEFTRIGGERDELAY);
}

void NGJoystickControl::registerAction(int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, int delay, joystickMovement movement, int triggerdelay) {
    if (_joystickActionCount < MAXJOYSTICKACTIONS) {
        joystickAction ja;
        ja.pin = pin;
        ja.mode = mode;
        ja.axis = axis;
        ja.kind = kind;
        ja.threshold = threshold;
        ja.delay = delay;
        ja.movement = movement;
        ja.triggerDelay = triggerdelay;
        _joystickActions[_joystickActionCount] = ja;
        _joystickActionCount++;
    }
}

void NGJoystickControl::processingLoop() {
    _lastAction = NOLASTACTIONID;
    // Analog 1..512..1023
    // Digital 1+e|512|e-1023
    switch(_kind) {
        case jkAnalog:
            _currentX = analogRead(_joystickPinX);
            _currentY = analogRead(_joystickPinY);
            break;
        case jkDigital:
            if (_digitalEpsilon == 0) {
                _digitalEpsilon = random(10, 20);
            } else {
                _digitalEpsilon = 0;
            }
            _currentX = 512;
            if (digitalRead(_joystickPinX) == LOW) {
                _currentX = 1 + _digitalEpsilon;
            } else if (digitalRead(_joystickPinX2) == LOW) {
                _currentX = 1023 - _digitalEpsilon;
            }
            _currentY = 512;
            if (digitalRead(_joystickPinY) == LOW) {
                _currentY = 1 + _digitalEpsilon;
            } else if (digitalRead(_joystickPinY2) == LOW) {
                _currentY = 1023 - _digitalEpsilon;
            }
            break;
    }
    for (int i = 0; i < _joystickActionCount; i++) {
        bool fire = false;
        bool inDelay = false;
        int value = 0;
        switch(_joystickActions[i].axis) {
            case jaX:
                if (_logXAxis) {
                    char log[100];
                    sprintf(log, "X: %d", _currentX);
                    Serial.println(log);
                }
                switch(_joystickActions[i].kind) {
                    case jtkLess:
                        fire = _currentX < _joystickActions[i].threshold;
                        if (fire) {
                            value = _currentX;
                        }
                        break;
                    case jtkGreater:
                        fire = _currentX > _joystickActions[i].threshold;
                        if (fire) {
                            value = _currentX;
                        }
                        break;
                }
                break;
            case jaY:
                if (_logYAxis) {
                    char log[100];
                    sprintf(log, "Y: %d", _currentY);
                    Serial.println(log);
                }
                switch(_joystickActions[i].kind) {
                    case jtkLess:
                        fire = _currentY < _joystickActions[i].threshold;
                        if (fire) {
                            value = _currentY;
                        }
                        break;
                    case jtkGreater:
                        fire = _currentY > _joystickActions[i].threshold;
                        if (fire) {
                            value = _currentY;
                        }
                        break;
                }
                break;
            case jaNone:
                if (_joystickPinFireHigh) {
                    fire = digitalRead(_joystickPinFire) == HIGH;
                } else {
                    fire = digitalRead(_joystickPinFire) == LOW;
                }
                break;
        }
        if (fire && _joystickActions[i].delay != NOJOYSTICKDELAY) {
            inDelay = millis() - _joystickActions[i].lastFire < _joystickActions[i].delay;
            fire = !inDelay;
        }
        if (_continuousFireThreshold > 0) {
            if (fire) {
                if (_joystickActions[i].axis == jaNone) {
                    _joystickActions[i].continuousFire++;
                    fire = _joystickActions[i].continuousFire < _continuousFireThreshold;
                }
            } else if (!inDelay && _joystickActions[i].continuousFire > 0) {
                _joystickActions[i].continuousFire--;
            }
        }
        int val = 0;
        if (fire) {
            _lastAction = i;
            switch(_joystickActions[i].mode) {
                case jamNone:
                    if (_actionValueCallback != nullptr) {
                        _actionValueCallback(_id, _joystickActions[_lastAction].movement, value);
                    }
                    break;
                case jamTriggerLOW:
                    digitalWrite(_joystickActions[_lastAction].pin, LOW);
                    delay(_joystickActions[_lastAction].triggerDelay);
                    digitalWrite(_joystickActions[_lastAction].pin, HIGH);
                    if (_actionCallback != nullptr) {
                        _actionCallback(_id, _joystickActions[_lastAction].movement);
                    }
                    break;
                case jamTriggerHIGH:
                    digitalWrite(_joystickActions[_lastAction].pin, HIGH);
                    delay(_joystickActions[_lastAction].triggerDelay);
                    digitalWrite(_joystickActions[_lastAction].pin, LOW);
                    if (_actionCallback != nullptr) {
                        _actionCallback(_id, _joystickActions[_lastAction].movement);
                    }
                    break;
                case jamMapping:
                    val = map(value, 0, _joystickActions[_lastAction].threshold, 0, _joystickActions[_lastAction].mapping) - _joystickActions[_lastAction].mapping;
                    if (val <= 1) {
                        val = 0;
                    }
                    if (_joystickActions[_lastAction].lastValue != val) {
                        if (_actionValueCallback != nullptr) {
                            _actionValueCallback(_id, _joystickActions[_lastAction].movement, val);
                        }
                        _joystickActions[_lastAction].lastValue = val;
                    }
                    break;
                case jamMappingInvers:
                    val = _joystickActions[_lastAction].mapping - map(value, 0, _joystickActions[_lastAction].threshold, 0, _joystickActions[_lastAction].mapping);
                    if (val <= 1) {
                        val = 0;
                    }
                    if (_joystickActions[_lastAction].lastValue != val) {
                        if (_actionValueCallback != nullptr) {
                            _actionValueCallback(_id, _joystickActions[_lastAction].movement, val);
                        }
                        _joystickActions[_lastAction].lastValue = val;
                    }
                    break;
            }
            _joystickActions[_lastAction].lastFire = millis();
            if (_logging) {
                char log[100];
                sprintf(log, "Joystick %d fired", _id);
                switch(_joystickActions[_lastAction].movement) {
                    case jmUp:
                        sprintf(log, "%s up", log);
                        break;
                    case jmDown:
                        sprintf(log, "%s down", log);
                        break;
                    case jmLeft:
                        sprintf(log, "%s left", log);
                        break;
                    case jmRight:
                        sprintf(log, "%s right", log);
                        break;
                    case jmFire:
                        sprintf(log, "%s button", log);
                        break;
                }
                Serial.println(log);
            }
            break;
        }
    }
}

int NGJoystickControl::getID() {
    return _id;
}

int NGJoystickControl::getX() {
    return _currentX;
}

int NGJoystickControl::getY() {
    return _currentY;
}

bool NGJoystickControl::hasLastMovement() {
    bool res = false;
    if (_lastAction != NOLASTACTIONID) {
        res = _joystickActions[_lastAction].movement != jmNone;
    }
    return res;
}

joystickMovement NGJoystickControl::getLastMovement() {
    joystickMovement res = jmNone;
    if (_lastAction != NOLASTACTIONID) {
        res = _joystickActions[_lastAction].movement;
    }
    return res;
}

int NGJoystickControl::getLastValue() {
    int res = 0;
    if (_lastAction != NOLASTACTIONID) {
        res = _joystickActions[_lastAction].lastValue;
    }
    return res;
}
