//
//  NGCompass.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 08.01.22.
//

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
    byte res = Wire.endTransmission();
    return res;
}

byte NGCompass::_readData(int *x, int *y, int *z) {
    Wire.beginTransmission(_address);
    Wire.write(0x00);
    byte res = Wire.endTransmission();
    Wire.requestFrom(_address, 6);
    *x = Wire.read(); //LSB  x
    *x |= Wire.read() << 8; //MSB  x
    *y = Wire.read(); //LSB  z
    *y |= Wire.read() << 8; //MSB z
    *z = Wire.read(); //LSB y
    *z |= Wire.read() << 8; //MSB y
    return res;
}

byte NGCompass::_setControlRegister(byte sampleRate, byte range, byte dataRate, byte mode) {
    return _writeRegister(COMPASSREGISTER09, sampleRate | range | dataRate | mode);
}

void NGCompass::initialize() {
    Wire.begin();
    reset();
    byte res = _setControlRegister(_sampleRate, _range, _dataRate, _mode);
    if (res != 0) {
        Serial.println(res);
    }
}

void NGCompass::reset() {
    byte res = _writeRegister(COMPASSREGISTER10, 0x80);
    if (res != 0) {
        Serial.println(res);
    }
    res = _writeRegister(COMPASSREGISTER11, 0x01);
    if (res != 0) {
        Serial.println(res);
    }
}

float NGCompass::getDirection() {
    int x = 0;
    int y = 0;
    int z = 0;
    byte err = _readData(&x, &y, &z);
    if (err != 0) {
        Serial.println(err);
    }
    Serial.println(x);
    Serial.println(y);
    Serial.println(z);
    float res = -atan2(y, x) * 180.0 / PI;
    return res + 180;
}

