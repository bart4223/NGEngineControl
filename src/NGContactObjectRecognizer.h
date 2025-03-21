//
//  NGContactObjectRecognizer.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.10.21.
//

#ifndef NGContactObjectRecognizer_h
#define NGContactObjectRecognizer_h

#include <Arduino.h>
#include <NGCustomObjectRecognizer.h>

#define DEF_INPUT_PIN A0

enum contactPinMode {cpmInput, cpmInputPullup};

class NGContactObjectRecognizer : public NGCustomObjectRecognizer {
    
private:
    byte _pin;
    contactPinMode _pinMode;
    bool _detected = false;
    
protected:
    void _create(contactPinMode pinMode, byte pin);
    
public:
    NGContactObjectRecognizer();
    
    NGContactObjectRecognizer(byte pin);
    
    NGContactObjectRecognizer(contactPinMode pinMode, byte pin);
    
    void initialize();
    
    bool detected();
    
    bool hasDetected();
    
    int getCloseness();
    
    char* getName();
};

#endif /* NGContactObjectRecognizer_h */
