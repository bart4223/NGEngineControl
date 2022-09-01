//
//  NGJoystickControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 13.08.22.
//

#include "NGJoystickControl.h"

NGJoystickControl::NGJoystickControl() {
    _create(NOJOYSTICKID, DEFJOYSTICKPINX, DEFJOYSTICKPINY, DEFJOYSTICKPINFIRE);
}

NGJoystickControl::NGJoystickControl(int id) {
    _create(id, DEFJOYSTICKPINX, DEFJOYSTICKPINY, DEFJOYSTICKPINFIRE);
}

NGJoystickControl::NGJoystickControl(byte joystickPinX, byte joystickPinY, byte joystickPinFire) {
    _create(NOJOYSTICKID, joystickPinX, joystickPinY, joystickPinFire);
}

NGJoystickControl::NGJoystickControl(int id, byte joystickPinX, byte joystickPinY, byte joystickPinFire) {
    _create(id, joystickPinX, joystickPinY, joystickPinFire);
}

void NGJoystickControl::_create(int id, byte joystickPinX, byte joystickPinY, byte joystickPinFire) {
    _id = id;
    _joystickPinX = joystickPinX;
    _joystickPinY = joystickPinY;
    _joystickPinFire = joystickPinFire;
}

void NGJoystickControl::initialize() {
    pinMode(_joystickPinFire, INPUT_PULLUP);
    for (int i = 0; i < _joystickActionCount; i++) {
        pinMode(_joystickActions[i].pin, OUTPUT);
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

void NGJoystickControl::registerActionCallback(joystickActionCallbackFunc callback) {
    _actionCallback = callback;
}

void NGJoystickControl::registerAction(int pin, joystickActionMode mode, joystickMovement movement) {
    registerAction(pin, mode, NOJOYSTICKDELAY, movement);
}

void NGJoystickControl::registerAction(int pin, joystickActionMode mode, int delay, joystickMovement movement) {
    registerAction(pin, mode, jaNone, jtkNone, NOJOYSTICKTHRESHOLD, delay, movement);
}

void NGJoystickControl::registerAction(int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, joystickMovement movement) {
    registerAction(pin, mode, axis, kind, threshold, NOJOYSTICKDELAY, movement);
}

void NGJoystickControl::registerAction(int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, int delay, joystickMovement movement) {
    if (_joystickActionCount < MAXJOYSTICKACTIONS) {
        joystickAction ja;
        ja.pin = pin;
        ja.mode = mode;
        ja.axis = axis;
        ja.kind = kind;
        ja.threshold = threshold;
        ja.delay = delay;
        ja.movement = movement;
        _joystickActions[_joystickActionCount] = ja;
        _joystickActionCount++;
    }
}

void NGJoystickControl::processingLoop() {
    _lastAction = NOLASTACTIONID;
    _currentX = analogRead(_joystickPinX);
    _currentY = analogRead(_joystickPinY);
    for (int i = 0; i < _joystickActionCount; i++) {
        bool fire = false;
        switch(_joystickActions[i].axis) {
            case jaX:
                switch(_joystickActions[i].kind) {
                    case jtkLess:
                        fire = _currentX < _joystickActions[i].threshold;
                        break;
                    case jtkGreater:
                        fire = _currentX > _joystickActions[i].threshold;
                        break;
                }
                break;
            case jaY:
                switch(_joystickActions[i].kind) {
                    case jtkLess:
                        fire = _currentY < _joystickActions[i].threshold;
                        break;
                    case jtkGreater:
                        fire = _currentY > _joystickActions[i].threshold;
                        break;
                }
                break;
            case jaNone:
                fire = digitalRead(_joystickPinFire) == LOW;
                break;
        }
        if (fire && _joystickActions[i].delay != NOJOYSTICKDELAY) {
            fire = millis() - _joystickActions[i].lastFire >= _joystickActions[i].delay;
        }
        if (fire) {
            _lastAction = i;
            switch(_joystickActions[i].mode) {
                case jamTriggerLOW:
                    digitalWrite(_joystickActions[i].pin, LOW);
                    delay(DEFTRIGGERDELAY);
                    digitalWrite(_joystickActions[i].pin, HIGH);
                    break;
                case jamTriggerHIGH:
                    digitalWrite(_joystickActions[i].pin, HIGH);
                    delay(DEFTRIGGERDELAY);
                    digitalWrite(_joystickActions[i].pin, LOW);
                    break;
            }
            _joystickActions[i].lastFire = millis();
            if (_actionCallback != nullptr) {
                _actionCallback(_id, _joystickActions[_lastAction].movement);
            }
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
