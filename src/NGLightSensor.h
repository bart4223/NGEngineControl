//
//  NGLightSensor.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.09.21.
//

#ifndef NGLightSensor_h
#define NGLightSensor_h

#include <Arduino.h>
#include <NGITestableComponent.h>

#define DEFPINLIGHTSENSOR A0
#define MAXTHRESHOLDCOUNT 5
#define DEFTHRESHOLDDELAY 2000
#define CDEFLOGDELAY 500

enum thresholdActionKind { takPin, takCallback };
enum thresholdLevel { tlUnder, tlOver };
enum thresholdValence { tvLow, tvHigh };

typedef void (*lightSensorCallbackFunc)(byte id);

struct sensorThresholdStruct
{
    thresholdActionKind actionKind;
    int threshold;
    thresholdLevel level;
    int delay;
    long lastAction;
    byte pin;
    thresholdValence valence;
    byte id;
    lightSensorCallbackFunc callback = nullptr;
};
typedef struct sensorThresholdStruct sensorThreshold;

class NGLightSensor : public NGITestableComponent {

private:
    byte _pinSensor;
    byte _thresholdCount;
    sensorThreshold _thresholds[MAXTHRESHOLDCOUNT];
    bool _logging = false;
    long _lastLog = 0;
    int _logDelay = CDEFLOGDELAY;
    
protected:
    void _create(byte pinSensor);
    
    void _raiseException(int id);
    
public:
    NGLightSensor();
    
    NGLightSensor(byte pinSensor);
    
    void initialize();
    
    void registerThreshold(int threshold, thresholdLevel level, byte pin, thresholdValence valence);
    
    void registerThreshold(int threshold, thresholdLevel level, byte pin, thresholdValence valence, int delay);
    
    void registerThreshold(int threshold, thresholdLevel level, byte id, lightSensorCallbackFunc callback);
    
    void registerThreshold(int threshold, thresholdLevel level, byte id, lightSensorCallbackFunc callback, int delay);
    
    void setLogging(bool logging);
    
    void setLogging(bool logging, int logdelay);
    
    bool getLogging();
    
    void determine();
    
    void testSequenceStart();
    
    void testSequenceStop();
    
    void processingLoop();
};

#endif /* NGLightSensor_h */
