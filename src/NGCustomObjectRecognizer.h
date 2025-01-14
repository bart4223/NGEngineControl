//
//  NGCustomObjectRecognizer.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.10.21.
//

#ifndef NGCustomObjectRecognizer_h
#define NGCustomObjectRecognizer_h

#include <Arduino.h>

class NGCustomObjectRecognizer {

public:
    virtual void initialize();
    
    virtual bool detected();
    
    virtual bool hasDetected();
    
    virtual int getCloseness();
    
    virtual char* getName();
};

#endif /* NGCustomObjectRecognizer_h */
