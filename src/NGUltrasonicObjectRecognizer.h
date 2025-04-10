//
//  NGUltrasonicObjectRecognizer.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 30.10.21.
//

#ifndef NGUltrasonicObjectRecognizer_h
#define NGUltrasonicObjectRecognizer_h

#include <Arduino.h>
#include <NGCustomObjectRecognizer.h>

#define ULTRASONICTIMEOUT 3000
#define DEFCOUNTMEASUREMENTS 2

class NGUltrasonicObjectRecognizer : public NGCustomObjectRecognizer {
    
private:
    byte _pinTrigger;
    byte _pinEcho;
    int _minDistance;
    int _maxDistance;
    bool _detected = false;
    int _countMeasurements = DEFCOUNTMEASUREMENTS;
    unsigned long _distance = 0.0;

protected:
    void _create(byte pinTrigger, byte pinEcho, int minDistance, int maxDistance);
    
public:
    NGUltrasonicObjectRecognizer(byte pinTrigger, byte pinEcho, int maxDistance);
    
    NGUltrasonicObjectRecognizer(byte pinTrigger, byte pinEcho, int minDistance, int maxDistance);
    
    void initialize();
    
    bool detected();
    
    bool hasDetected();
    
    int getCloseness();
    
    char* getName();
};

#endif /* NGUltrasonicObjectRecognizer_h */
