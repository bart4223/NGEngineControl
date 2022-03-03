//
//  NGGyroscope.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.02.22.
//

#include "Wire.h"
#include "NGGyroscope.h"

NGGyroscope::NGGyroscope() {
    _create();
}

void NGGyroscope::_create() {
}

void NGGyroscope::_readData() {
    uint8_t adr = _address;
    uint8_t len = 14;
    Wire.beginTransmission(_address);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(adr, len, true);
    for (int i = 0; i < 3; i++) {
        _accelerator[i] = Wire.read() << 8 | Wire.read();
        int accCorr = _accelerator[i] - ACCELOFFSET;
        accCorr = map(accCorr, -16800, 16800, -90, 90);
        _acceleratorAngle[i] = constrain(accCorr, -90, 90);
    }
    _temperature = Wire.read() << 8 | Wire.read();
    for (int i = 0; i < 3; i++) {
        _gyroscope[i] = Wire.read() << 8 | Wire.read();
        _gyroscopeAngle[i] = (float)(_gyroscale * _gyroscope[i] / GYROSENSITITY * DEFGYRORANGE);
    }
}

void NGGyroscope::initialize() {
    Wire.begin();
    Wire.beginTransmission(_address);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
}

void NGGyroscope::processingLoop() {
    _readData();
}

void NGGyroscope::getGyroscopeAngle(float *angleX, float *angleY, float *angleZ) {
    *angleX = _gyroscopeAngle[0];
    *angleY = _gyroscopeAngle[1];
    *angleZ = _gyroscopeAngle[2];
}

int NGGyroscope::getTemperature() {
    return (_temperature + 12412.0) / 340.0;
}

void NGGyroscope::setThreshold(int thresholdX, int thresholdY, int thresholdZ) {
    _thresholdX = thresholdX;
    _thresholdY = thresholdY;
    _thresholdZ = thresholdZ;
}

bool NGGyroscope::isGyroscopeRaisedX() {
    return _gyroscopeAngle[0] >= _thresholdX;
}

bool NGGyroscope::isGyroscopeRaisedY() {
    return _gyroscopeAngle[1] >= _thresholdY;
}

bool NGGyroscope::isGyroscopeRaisedZ() {
    return _gyroscopeAngle[2] >= _thresholdZ;
}
