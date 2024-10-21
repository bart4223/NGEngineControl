//
//  NGDigitalPotentiometer.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 21.10.24.
//

#include <SPI.h>
#include "NGDigitalPotentiometer.h"

NGDigitalPotentiometer::NGDigitalPotentiometer(byte pincs, byte address) {
    _create(pincs, address);
}

void NGDigitalPotentiometer::_create(byte pincs, byte address) {
    _pinCS = pincs;
    _address = address;
}

void NGDigitalPotentiometer::initialize(byte initvalue) {
    initialize();
    setValue(initvalue);
}

void NGDigitalPotentiometer::initialize() {
    pinMode(_pinCS, OUTPUT);
    SPI.begin();
    setValue(_minValue);
}

void NGDigitalPotentiometer::setMinValue(byte minvalue) {
    _minValue = minvalue;
}

void NGDigitalPotentiometer::setMaxValue(byte maxvalue) {
    _maxValue = maxvalue;
}

void NGDigitalPotentiometer::setStepValue(byte stepvalue) {
    _stepValue = stepvalue;
}

void NGDigitalPotentiometer::setValue(byte value) {
    if (_value != value) {
        _value = value;
        digitalWrite(_pinCS, LOW);
        SPI.transfer(_address);
        SPI.transfer(_value);
        digitalWrite(_pinCS, HIGH);
    }
}

byte NGDigitalPotentiometer::getValue() {
    return _value;
}

void NGDigitalPotentiometer::incrementValue() {
    int value = getValue();
    if (value + _stepValue <= _maxValue) {
        value = value + _stepValue;
    } else {
        value = _maxValue;
    }
    setValue(value);
}

void NGDigitalPotentiometer::decrementValue() {
    byte value = getValue();
    if (value - _stepValue >= _minValue) {
        value = value - _stepValue;
    } else {
        value = _minValue;
    }
    setValue(value);
}

void NGDigitalPotentiometer::changeValue() {
    switch(_direction) {
        case dpdUp:
            if (getValue() == _maxValue) {
                _direction = dpdDown;
                decrementValue();
            } else {
                incrementValue();
            }
            break;
        case dpdDown:
            if (getValue() == _minValue) {
                _direction = dpdUp;
                incrementValue();
            } else {
                decrementValue();
            }
            break;
    }
}
