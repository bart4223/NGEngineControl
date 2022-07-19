//
//  NGCurrentSensor.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 16.07.22.
//

#include "NGCurrentSensor.h"

NGCurrentSensor::NGCurrentSensor() {
    _create(DEFCURRENTSENSORTECHNOLOGY, DEFPINLIGHTSENSOR);
}

NGCurrentSensor::NGCurrentSensor(byte pinSensor) {
    _create(DEFCURRENTSENSORTECHNOLOGY, pinSensor);
}

NGCurrentSensor::NGCurrentSensor(CurrentSensorTechnology sensorTechnology) {
    _create(sensorTechnology, DEFPINLIGHTSENSOR);
}

NGCurrentSensor::NGCurrentSensor(CurrentSensorTechnology sensorTechnology, byte pinSensor) {
    _create(sensorTechnology, pinSensor);
}

void NGCurrentSensor::_create(CurrentSensorTechnology sensorTechnology, byte pinSensor) {
    _pinSensor = pinSensor;
    _sensorTechnology = sensorTechnology;
}

void NGCurrentSensor::_determineCurrent() {
    int value = analogRead(_pinSensor);
    value = ((((value / 1024.0) * 5000) - 2500) / _mVpA) * 1000;
    if (value < 0) {
        _currentCurrent = value * -1;
    } else {
        _currentCurrent = value;
    }
    if (_currentCurrent > _maxCurrent) {
        _maxCurrent = _currentCurrent;
    }
    if (_currentCurrent < _minCurrent) {
        _minCurrent = _currentCurrent;
    }
}

void NGCurrentSensor::initialize() {
    switch(_sensorTechnology) {
        case cst5Ampere:
            _mVpA = 185;
            break;
        case cst20Ampere:
            _mVpA = 100;
            break;
        case cst30Ampere:
            _mVpA = 66;
            break;
    }
}

int NGCurrentSensor::getCurrent() {
    _determineCurrent();
    return _currentCurrent;
}

int NGCurrentSensor::getMin() {
    return _minCurrent;
}

int NGCurrentSensor::getMax() {
    return _maxCurrent;
}

void NGCurrentSensor::reset() {
    _minCurrent = DEFMINCURRENT;
    _maxCurrent = 0;
}
