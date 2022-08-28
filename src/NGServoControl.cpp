//
//  NGServoControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 26.08.22.
//

#include "NGServoControl.h"

NGServoControl::NGServoControl(byte pinServo) {
    _create(pinServo, DEFSERVOZEROPOSITION, DEFSERVOMINPOSITION, DEFSERVOMAXPOSITION, DEFSERVOSTEPWIDTH);
}

NGServoControl::NGServoControl(byte pinServo, byte zeroPosition) {
    _create(pinServo, zeroPosition, DEFSERVOMINPOSITION, DEFSERVOMAXPOSITION, DEFSERVOSTEPWIDTH);
}

NGServoControl::NGServoControl(byte pinServo, byte zeroPosition, byte minPosition, byte maxPosition) {
    _create(pinServo, zeroPosition, minPosition, maxPosition, DEFSERVOSTEPWIDTH);
}

NGServoControl::NGServoControl(byte pinServo, byte zeroPosition, byte minPosition, byte maxPosition, byte stepWidth) {
    _create(pinServo, zeroPosition, minPosition, maxPosition, stepWidth);
}

NGServoControl::_create(byte pinServo, byte zeroPosition, byte minPosition, byte maxPosition, byte stepWidth) {
    _initialized = false;
    _Servo = new Servo();
    _pinServo = pinServo;
    _zeroPosition = zeroPosition;
    _minPosition = minPosition;
    _maxPosition = maxPosition;
    _stepWidth = stepWidth;
    _logging = true;
}

void NGServoControl::initialize() {
    char log[100];
    _Servo->attach(_pinServo);
    _initialized = true;
    if (_logging) {
        sprintf(log, "Servo at pin %d initialized", _pinServo);
        Serial.println(log);
    }
    reset();
}

void NGServoControl::setPosition(byte pos) {
    char log[100];
    _position = pos;
    if (_position < _minPosition) {
        _position = _minPosition;
    } else if (_position > _maxPosition) {
        _position = _maxPosition;
    }
    _Servo->write(_position);
    if (_logging) {
        sprintf(log, "Servo pos %d", _position);
        Serial.println(log);
    }
}

byte NGServoControl::getPosition() {
    return _position;
}

void NGServoControl::reset() {
    setPosition(_zeroPosition);
}

void NGServoControl::stepUp() {
    int pos = _position + _stepWidth;
    if (pos > _maxPosition) {
        pos = _maxPosition;
    }
    setPosition(pos);
}

void NGServoControl::stepDown() {
    int pos = _position - _stepWidth;
    if (pos < _minPosition) {
        pos = _minPosition;
    }
    setPosition(pos);
}

bool NGServoControl::isMinPosition() {
    return _position == _minPosition;
}

bool NGServoControl::isMaxPosition() {
    return _position == _maxPosition;
}
