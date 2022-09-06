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

#include <NGITestableComponent.h>

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

class NGLightSensor : public NGITestableComponent {

private:
    byte _pinSensor;
    byte _thresholdCount;
    sensorThreshold _thresholds[MAXTHRESHOLDCOUNT];
    
protected:
    void _create(byte pinSensor);
    
public:
    NGLightSensor();
    
    NGLightSensor(byte pinSensor);
    
    void initialize();
    
    void registerThreshold(int threshold, thresholdLevel level, byte pin, thresholdValence valence);
    
    void registerThreshold(int threshold, thresholdLevel level, byte pin, thresholdValence valence, int delay);
    
    void determine();
    
    void testSequenceStart();
    
    void testSequenceStop();
};

#endif /* NGLightSensor_h */
