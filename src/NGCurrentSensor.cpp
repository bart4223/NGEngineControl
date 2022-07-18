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

NGCurrentSensor::_create(CurrentSensorTechnology sensorTechnology, byte pinSensor) {
    _pinSensor = pinSensor;
    _sensorTechnology = sensorTechnology;
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
    int sensorvalue = analogRead(_pinSensor);
    return ((((sensorvalue / 1024.0) * 5000) - 2500) / _mVpA) * 1000;
}

int NGCurrentSensor::getCurrentAbs() {
    int res = getCurrent();
    if (res < 0) {
        res = res * -1;
    }
    return res;
}
