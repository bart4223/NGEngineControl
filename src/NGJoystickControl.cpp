//
//  NGJoystickControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 13.08.22.
//

#include "NGJoystickControl.h"

NGJoystickControl::NGJoystickControl() {
    _create(DEFJOYSTICKPINX, DEFJOYSTICKPINY);
}

NGJoystickControl::NGJoystickControl(byte joystickPinX, byte joystickPinY) {
    _create(joystickPinX, joystickPinY);
}

void NGJoystickControl::_create(byte joystickPinX, byte joystickPinY) {
    _joystickPinX = joystickPinX;
    _joystickPinY = joystickPinY;
}

void NGJoystickControl::initialize() {
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

void NGJoystickControl::registerAction(int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold) {
    registerAction(pin, mode, axis, kind, threshold, NOJOYSTICKDELAY);
}

void NGJoystickControl::registerAction(int pin, joystickActionMode mode, joystickAxis axis, joystickThresholdKind kind, int threshold, int delay) {
    if (_joystickActionCount < MAXJOYSTICKACTIONS) {
        joystickAction ja;
        ja.pin = pin;
        ja.mode = mode;
        ja.axis = axis;
        ja.kind = kind;
        ja.threshold = threshold;
        ja.delay = delay;
        _joystickActions[_joystickActionCount] = ja;
        _joystickActionCount++;
    }
}

void NGJoystickControl::processingLoop() {
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
        }
        if (fire && _joystickActions[i].delay != NOJOYSTICKDELAY) {
            fire = millis() - _joystickActions[i].lastFire >= _joystickActions[i].delay;
        }
        if (fire) {
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
        }
    }
}

int NGJoystickControl::getX() {
    return _currentX;
}

int NGJoystickControl::getY() {
    return _currentY;
}
