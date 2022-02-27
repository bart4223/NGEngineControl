//
//  NGTimeOfFlightObjectRecognizer.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.02.22.
//

#include "Wire.h"
#include "NGTimeOfFlightObjectRecognizer.h"

NGTimeOfFlightObjectRecognizer::NGTimeOfFlightObjectRecognizer(int maxDistance) {
    _create(0, maxDistance);
}

NGTimeOfFlightObjectRecognizer::NGTimeOfFlightObjectRecognizer(int minDistance, int maxDistance) {
    _create(minDistance, maxDistance);
}

void NGTimeOfFlightObjectRecognizer::_create(int minDistance, int maxDistance) {
    Wire.begin();
    _sensor = new VL53L0X();
    _minDistance = minDistance;
    _maxDistance = maxDistance;
}

void NGTimeOfFlightObjectRecognizer::initialize() {
    _sensor->init();
    _sensor->startContinuous();
}

bool NGTimeOfFlightObjectRecognizer::detected() {
    _distance = _sensor->readRangeContinuousMillimeters() / 10;
    _detected = (_distance > _minDistance && _distance <= _maxDistance);
    return _detected;
}

bool NGTimeOfFlightObjectRecognizer::hasDetected() {
    return _detected;
}

int NGTimeOfFlightObjectRecognizer::getCloseness() {
    return (int)_distance;
}

char* NGTimeOfFlightObjectRecognizer::getName() {
    return (char*)"TimeOfFlight";
}
