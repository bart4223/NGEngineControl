//
//  NGDuoLED.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.12.21.
//

#include "NGDuoLED.h"

NGDuoLED::NGDuoLED(byte pinLEDOne, byte pinLEDTwo) {
    _create(pinLEDOne, pinLEDTwo);
}

void NGDuoLED::_create(byte pinLEDOne, byte pinLEDTwo) {
    _pinLEDOne = pinLEDOne;
    _pinLEDTwo = pinLEDTwo;
}

void NGDuoLED::initialize() {
    pinMode(_pinLEDOne, OUTPUT);
    pinMode(_pinLEDTwo, OUTPUT);
    turnOff();
}

void NGDuoLED::turnOneOff() {
    digitalWrite(_pinLEDOne, LOW);
    _isOneOn = false;
}

void NGDuoLED::turnTwoOff() {
    digitalWrite(_pinLEDTwo, LOW);
    _isTwoOn = false;
}

void NGDuoLED::turnOff() {
    turnOneOff();
    turnTwoOff();
}

void NGDuoLED::turnOneOn() {
    digitalWrite(_pinLEDOne, HIGH);
    _isOneOn = true;
}

void NGDuoLED::turnTwoOn() {
    digitalWrite(_pinLEDTwo, HIGH);
    _isTwoOn = true;
}

void NGDuoLED::turnOn() {
    turnOneOn();
    turnTwoOn();
}

bool NGDuoLED::isOneOn() {
    return _isOneOn;
}

bool NGDuoLED::isTwoOn() {
    return _isTwoOn;
}

bool NGDuoLED::isOn() {
    return _isOneOn && _isTwoOn;
}

void NGDuoLED::toggle() {
    if (!isOneOn() && !isTwoOn()) {
        turnOneOn();
    } else if (isOneOn()) {
        turnOneOff();
        turnTwoOn();
    } else {
        turnOneOn();
        turnTwoOff();
    }
}
