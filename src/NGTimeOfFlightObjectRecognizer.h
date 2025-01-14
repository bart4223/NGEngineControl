//
//  NGTimeOfFlightObjectRecognizer.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.02.22.
//

#ifndef NGTimeOfFlightObjectRecognizer_h
#define NGTimeOfFlightObjectRecognizer_h

#include <Arduino.h>
#include <VL53L0X.h>
#include <NGCustomObjectRecognizer.h>

class NGTimeOfFlightObjectRecognizer : public NGCustomObjectRecognizer {
  
private:
    VL53L0X *_sensor;
    int _minDistance;
    int _maxDistance;
    bool _detected = false;
    unsigned long _distance = 0.0;
    
protected:
    void _create(int minDistance, int maxDistance);
    
public:
    NGTimeOfFlightObjectRecognizer(int maxDistance);
    
    NGTimeOfFlightObjectRecognizer(int minDistance, int maxDistance);
    
    void initialize();
    
    bool detected();
    
    bool hasDetected();
    
    int getCloseness();
    
    char* getName();
};

#endif /* NGTimeOfFlightObjectRecognizer_h */
