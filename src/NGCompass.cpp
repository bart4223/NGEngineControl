//
//  NGCompass.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 08.01.22.
//

#include "Wire.h"
#include "NGCompass.h"

NGCompass::NGCompass() {
    _create(COMPASSADDRESS, COMPASSOSR_128, COMPASSRNG_2G, COMPASSODR_100HZ, COMPASSMODECONTINUOUS);
}

NGCompass::NGCompass(byte address) {
    _create(address, COMPASSOSR_128, COMPASSRNG_2G, COMPASSODR_100HZ, COMPASSMODECONTINUOUS);
}

NGCompass::_create(byte address, byte sampleRate, byte range, byte dataRate, byte mode) {
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
    Wire.beginTransmission(_address);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(_address, 6);
    *x = Wire.read();
    *x |= Wire.read() << 8;
    *y = Wire.read();
    *y |= Wire.read() << 8;
    *z = Wire.read();
    *z |= Wire.read() << 8;
}

byte NGCompass::_setControlRegister(byte sampleRate, byte range, byte dataRate, byte mode) {
    return _writeRegister(COMPASSREGISTER09, sampleRate | range | dataRate | mode);
}

void NGCompass::initialize() {
    Wire.begin();
    reset();
    _setControlRegister(_sampleRate, _range, _dataRate, _mode);
}

void NGCompass::reset() {
    _writeRegister(COMPASSREGISTER10, 0x80);
}

float NGCompass::getDirection() {
    int x, y, z;
    _readData(&x, &y, &z);
    float res = -atan2(y, x) * 180.0 / PI;
    return res + 180;
}

