//
//  NGLaserCannon.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.10.21.
//

#include "NGLaserCannon.h"

NGLaserCannon::NGLaserCannon(byte pinLaserCannon) {
    _create(pinLaserCannon);
}

void NGLaserCannon::_create(byte pinLaserCannon) {
    _pinLaserCannon = pinLaserCannon;
}

void NGLaserCannon::initialize() {
    pinMode(_pinLaserCannon, OUTPUT);
    fireOff();
}

void NGLaserCannon::fireOn() {
    digitalWrite(_pinLaserCannon, HIGH);
    _fire = true;
}

void NGLaserCannon::fireOff() {
    digitalWrite(_pinLaserCannon, LOW);
    _fire = false;
}

bool NGLaserCannon::isFire() {
    return _fire;
}

void NGLaserCannon::testSequenceStart() {
    initialize();
    fireOn();
}

void NGLaserCannon::testSequenceStop() {
    fireOff();
}
