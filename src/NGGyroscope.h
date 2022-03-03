//
//  NGGyroscope.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.02.22.
//

#ifndef NGGyroscope_h
#define NGGyroscope_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define MPUADDRESS 0x68

#define ACCELOFFSET     200
#define GYROSENSITITY   131
#define DEFGYRORANGE    250
#define DEFGYROSCALE    0.01

class NGGyroscope {
    
private:
    byte _address = MPUADDRESS;
    int _accelerator[3];
    int _acceleratorAngle[3];
    int _gyroscope[3];
    float _gyroscopeAngle[3];
    float _gyroscale = DEFGYROSCALE;
    int _temperature;
    int _thresholdX = 0;
    int _thresholdY = 0;
    int _thresholdZ = 0;
    
protected:
    void _create();
    
    void _readData();
    
public:
    NGGyroscope();
    
    void initialize();
    
    void getGyroscopeAngle(float *angleX, float *angleY, float *angleZ);
    
    int getTemperature();
    
    void setThreshold(int thresholdX, int thresholdY, int thresholdZ);
    
    void processingLoop();
    
    bool isGyroscopeRaisedX();
    
    bool isGyroscopeRaisedY();
    
    bool isGyroscopeRaisedZ();
};

#endif /* NGGyroscope_h */
