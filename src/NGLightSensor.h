//
//  NGLightSensor.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.09.21.
//

#ifndef NGLightSensor_h
#define NGLightSensor_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define DEFPINLIGHTSENSOR A0
#define MAXTHRESHOLDCOUNT 5
#define DEFTHRESHOLDDELAY 2000

enum thresholdLevel { tlUnder, tlOver };
enum thresholdValence { tvLow, tvHigh };

struct sensorThresholdStruct
{
    int threshold;
    thresholdLevel level;
    byte pin;
    thresholdValence valence;
    int delay;
    int counter;
};
typedef struct sensorThresholdStruct sensorThreshold;

class NGLightSensor {

private:
    byte _pinSensor;
    byte _thresholdCount;
    sensorThreshold _thresholds[MAXTHRESHOLDCOUNT];
    
protected:
    _create(byte pinSensor);
    
public:
    NGLightSensor();
    
    NGLightSensor(byte pinSensor);
    
    void initialize();
    
    void registerThreshold(int threshold, thresholdLevel level, byte pin, thresholdValence valence);
    
    void registerThreshold(int threshold, thresholdLevel level, byte pin, thresholdValence valence, int delay);
    
    void determine();
};

#endif /* NGLightSensor_h */
