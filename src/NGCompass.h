//
//  NGCompass.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 08.01.22.
//

#ifndef NGCompass_h
#define NGCompass_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// GY-271 - QMC5883L
// Control-Register 0x09, 0x0A and 0x0B

#define COMPASSADDRESS      0x1E
#define COMPASSREGISTER09   0x09
#define COMPASSREGISTER10   0x0A
#define COMPASSREGISTER11   0x0B

#define COMPASSMODESTANDBY      0x00
#define COMPASSMODECONTINUOUS   0x01

#define COMPASSODR_10HZ     0x00
#define COMPASSODR_50HZ     0x04
#define COMPASSODR_100HZ    0x08
#define COMPASSODR_200HZ    0x0C

#define COMPASSRNG_2G   0x00
#define COMPASSRNG_8G   0x10

#define COMPASSOSR_512  0x00
#define COMPASSOSR_256  0x40
#define COMPASSOSR_128  0x80
#define COMPASSOSR_64   0xC0

class NGCompass {
    
private:
    byte _address;
    byte _sampleRate;
    byte _range;
    byte _dataRate;
    byte _mode;
    
protected:
    _create(byte address, byte sampleRate, byte range, byte dataRate, byte mode);
    
    byte _writeRegister(byte reg, byte val);
    
    void _readData(int *x, int *y, int *z);
    
    byte _setControlRegister(byte sampleRate, byte range, byte dataRate, byte mode);
    
public:
    NGCompass();
    
    NGCompass(byte address);
    
    void initialize();
    
    void reset();
    
    float getDirection();
};

#endif /* NGCompass_h */
