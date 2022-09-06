//
//  NGCompass.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 08.01.22.
//

#include "Wire.h"
#include "NGCompass.h"

NGCompass::NGCompass() {
    _create(cttQMC, QMCADDRESS, QMCOSR_128, QMCRNG_8G, QMCODR_100HZ, QMCMODECONTINUOUS);
}

NGCompass::NGCompass(compassTechnologyType type) {
    switch(type) {
        case cttQMC:
            _create(type, QMCADDRESS, QMCOSR_128, QMCRNG_8G, QMCODR_100HZ, QMCMODECONTINUOUS);
            break;
        case cttHMC:
            _create(type, HMCADDRESS, HMCOSR_128, HMCRNG_8G, HMCODR_100HZ, HMCMEASUREMENTCONTINUOUS);
            break;
    }
}

NGCompass::NGCompass(byte address) {
    _create(cttQMC, address, QMCOSR_128, QMCRNG_8G, QMCODR_100HZ, QMCMODECONTINUOUS);
}

NGCompass::NGCompass(compassTechnologyType type, byte address) {
    switch(type) {
        case cttQMC:
            _create(type, address, QMCOSR_128, QMCRNG_8G, QMCODR_100HZ, QMCMODECONTINUOUS);
            break;
        case cttHMC:
            _create(type, address, HMCOSR_128, HMCRNG_8G, HMCODR_100HZ, HMCMEASUREMENTCONTINUOUS);
            break;
    }
}

void NGCompass::_create(compassTechnologyType type, byte address, byte sampleRate, byte range, byte dataRate, byte mode) {
    _type = type;
    _address = address;
    _sampleRate = sampleRate;
    _range = range;
    _dataRate = dataRate;
    _mode = mode;
}

byte NGCompass::_writeRegister(byte reg, byte val) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(val);
    return Wire.endTransmission();
}

void NGCompass::_readData(int *x, int *y, int *z) {
    uint8_t adr = _address;
    uint8_t len = 6;
    switch (_type) {
        case cttQMC:
            Wire.beginTransmission(_address);
            Wire.write(0x00);
            Wire.endTransmission();
            Wire.requestFrom(adr, len);
            *x = Wire.read();
            *x |= Wire.read() << 8;
            *y = Wire.read();
            *y |= Wire.read() << 8;
            *z = Wire.read();
            *z |= Wire.read() << 8;
            break;
        case cttHMC:
            Wire.beginTransmission(_address);
            Wire.write(HMCDATAREGISTERBEGIN);
            Wire.endTransmission();
            Wire.beginTransmission(_address);
            Wire.requestFrom(adr, len);
            *x = Wire.read() << 8;
            *x |= Wire.read();
            *z = Wire.read() << 8;
            *z |= Wire.read();
            *y = Wire.read() << 8;
            *y |= Wire.read();
            Wire.endTransmission();
            break;
    }
    if (_useCalibration) {
        int offsetX = (_calibration[0][0] + _calibration[0][1]) / 2;
        int offsetY = (_calibration[1][0] + _calibration[1][1]) / 2;
        int offsetZ = (_calibration[2][0] + _calibration[2][1]) / 2;
        int averageDeltaX = (_calibration[0][1] - _calibration[0][0]) / 2;
        int averageDeltaY = (_calibration[1][1] - _calibration[1][0]) / 2;
        int averageDeltaZ = (_calibration[2][1] - _calibration[2][0]) / 2;
        int averageDelta = (averageDeltaX + averageDeltaY + averageDeltaZ) / 3;
        float scaleX = (float)averageDelta / averageDeltaX;
        float scaleY = (float)averageDelta / averageDeltaY;
        float scaleZ = (float)averageDelta / averageDeltaZ;
        *x = (*x - offsetX) * scaleX;
        *y = (*y - offsetY) * scaleY;
        *z = (*z - offsetZ) * scaleZ;
    }
}

void NGCompass::initialize() {
    Wire.begin();
    switch (_type) {
        case cttQMC:
            _writeRegister(QMCREGISTER10, QMCRESET); // RESET
            _writeRegister(QMCREGISTER11, QMCMODECONTINUOUS); // SET/RESET-Period
            _writeRegister(QMCREGISTER09, _sampleRate | _range | _dataRate | _mode); // MODE
            break;
        case cttHMC:
            _writeRegister(HMCMODEREGISTER, HMCMEASUREMENTCONTINUOUS); // MODE
            break;
    }
}

void NGCompass::setDeclination(float declination) {
    _declination = declination;
}

void NGCompass::setDirectionOffset(int directionOffset) {
    _directionOffset = directionOffset;
}

void NGCompass::setCalibration(int minX, int maxX, int minY, int maxY, int minZ, int maxZ) {
    _useCalibration = true;
    _calibration[0][0] = minX;
    _calibration[0][1] = maxX;
    _calibration[1][0] = minY;
    _calibration[1][1] = maxY;
    _calibration[2][0] = minZ;
    _calibration[2][1] = maxZ;
}

float NGCompass::getDirection() {
    int x, y, z;
    float res;
    _readData(&x, &y, &z);
    switch (_type) {
        case cttQMC:
            res = atan2(y, x) * 180.0 / PI;
            if (res < 0) {
                res += 360;
            }
            break;
        case cttHMC:
            res = atan2(y, x) + _declination;
            if (res < 0) {
                res += 2 * PI;
            }
            if (res > 2 * PI) {
                res -= 2 * PI;
            }
            res = res * 180.0 / PI;
            break;
    }
    res += _directionOffset;
    if (res < 0) {
        res += 360;
    } else if (res > 360) {
        res -= 360;
    }
    return res;
}
