//
//  NGUltrasonicObjectRecognizer.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 30.10.21.
//

#include "NGUltrasonicObjectRecognizer.h"

NGUltrasonicObjectRecognizer::NGUltrasonicObjectRecognizer(byte pinTrigger, byte pinEcho, int maxDistance) {
    _create(pinTrigger, pinEcho, 0, maxDistance);
}

NGUltrasonicObjectRecognizer::NGUltrasonicObjectRecognizer(byte pinTrigger, byte pinEcho, int minDistance, int maxDistance) {
    _create(pinTrigger, pinEcho, minDistance, maxDistance);
}

void NGUltrasonicObjectRecognizer::_create(byte pinTrigger, byte pinEcho, int minDistance, int maxDistance) {
    _pinTrigger = pinTrigger;
    _pinEcho = pinEcho;
    _minDistance = minDistance;
    _maxDistance = maxDistance;
}

void NGUltrasonicObjectRecognizer::initialize() {
    pinMode(_pinTrigger, OUTPUT);
    pinMode(_pinEcho, INPUT);
}

bool NGUltrasonicObjectRecognizer::detected() {
    unsigned long duration, distance;
    digitalWrite(_pinTrigger, LOW);
    delayMicroseconds(2);
    digitalWrite(_pinTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(_pinTrigger, LOW);
    duration = pulseIn(_pinEcho, HIGH, ULTRASONICTIMEOUT);
    distance = duration / 58.224; // cm
    _detected = (distance > _minDistance && distance <= _maxDistance);
    return _detected;
}

bool NGUltrasonicObjectRecognizer::hasDetected() {
    return _detected;
}
