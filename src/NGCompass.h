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

#define QMCADDRESS      0x0D

#define QMCREGISTER09   0x09
#define QMCREGISTER10   0x0A
#define QMCREGISTER11   0x0B

#define QMCRESET   0x80

#define QMCMODESTANDBY      0x00
#define QMCMODECONTINUOUS   0x01

#define QMCODR_10HZ     0x00
#define QMCODR_50HZ     0x04
#define QMCODR_100HZ    0x08
#define QMCODR_200HZ    0x0C

#define QMCRNG_2G   0x00
#define QMCRNG_8G   0x10

#define QMCOSR_512  0x00
#define QMCOSR_256  0x40
#define QMCOSR_128  0x80
#define QMCOSR_64   0xC0

// GY-271 - HMC5883 or L883
// Control-Register 0x00, 0x01 , 0x02 and 0x03

#define HMCADDRESS              0x1E
#define HMCCONFIGREGISTERA      0x00
#define HMCCONFIGREGISTERB      0x01
#define HMCMODEREGISTER         0x02
#define HMCDATAREGISTERBEGIN    0x03

#define HMCMEASUREMENTCONTINUOUS    0x00
#define HMCMEASUREMENTSINGLESHOT    0x01
#define HMCMEASUREMENTIDLE          0x03

#define HMCODR_10HZ     0x00
#define HMCODR_50HZ     0x04
#define HMCODR_100HZ    0x08
#define HMCODR_200HZ    0x0C

#define HMCRNG_2G   0x00
#define HMCRNG_8G   0x10

#define HMCOSR_512  0x00
#define HMCOSR_256  0x40
#define HMCOSR_128  0x80
#define HMCOSR_64   0xC0

enum compassTechnologyType {cttQMC, cttHMC};

class NGCompass {
    
private:
    compassTechnologyType _type;
    byte _address;
    byte _sampleRate;
    byte _range;
    byte _dataRate;
    byte _mode;
    int _directionOffset = 0;
    float _declination = 0.08203;
    bool _useCalibration = false;
    int _calibration[3][2];
    int _calibrated[3];
    
protected:
    void _create(compassTechnologyType type, byte address, byte sampleRate, byte range, byte dataRate, byte mode);
    
    byte _writeRegister(byte reg, byte val);
    
    void _readData(int *x, int *y, int *z);
        
public:
    NGCompass();
    
    NGCompass(compassTechnologyType type);
    
    NGCompass(byte address);
    
    NGCompass(compassTechnologyType type, byte address);
    
    void initialize();
    
    void setDeclination(float declination);
    
    void setDirectionOffset(int directionOffset);
    
    void setCalibration(int minX, int maxX, int minY, int maxY, int minZ, int maxZ);
    
    float getDirection();
};

#endif /* NGCompass_h */
