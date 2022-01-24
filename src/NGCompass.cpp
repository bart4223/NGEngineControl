//
//  NGCompass.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 08.01.22.
//

#include "Wire.h"
#include "NGCompass.h"

NGCompass::NGCompass() {
    _create(cttQMC, QMCADDRESS, QMCOSR_128, QMCRNG_2G, QMCODR_100HZ, QMCMODECONTINUOUS);
}

NGCompass::NGCompass(compassTechnologyType type) {
    _create(type, QMCADDRESS, QMCOSR_128, QMCRNG_2G, QMCODR_100HZ, QMCMODECONTINUOUS);
}

NGCompass::NGCompass(byte address) {
    _create(cttQMC, address, QMCOSR_128, QMCRNG_2G, QMCODR_100HZ, QMCMODECONTINUOUS);
}

NGCompass::NGCompass(compassTechnologyType type, byte address) {
    _create(type, address, QMCOSR_128, QMCRNG_2G, QMCODR_100HZ, QMCMODECONTINUOUS);
}

NGCompass::_create(compassTechnologyType type, byte address, byte sampleRate, byte range, byte dataRate, byte mode) {
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
}

void NGCompass::initialize() {
    Wire.begin();
    switch (_type) {
        case cttQMC:
            _writeRegister(QMCREGISTER10, 0x80); // RESET
            _writeRegister(QMCREGISTER09, _sampleRate | _range | _dataRate | _mode); // MODE
            _writeRegister(QMCREGISTER11, 0x01); // SET/RESET-Period
            break;
        case cttHMC:
            _writeRegister(HMCMODEREGISTER, HMCMEASUREMENTCONTINUOUS);
            break;
    }
}

void NGCompass::setDeclination(float declination) {
    _declination = declination;
}

float NGCompass::getDirection() {
    int x, y, z;
    float res;
    _readData(&x, &y, &z);
    switch (_type) {
        case cttQMC:
            res = -atan2(y, x) * 180.0 / PI;
            res += 180.0;
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
    return res;
}
