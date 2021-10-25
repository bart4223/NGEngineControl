//
//  NGCustomObjectRecognizer.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.10.21.
//

#ifndef NGCustomObjectRecognizer_h
#define NGCustomObjectRecognizer_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class NGCustomObjectRecognizer {

public:
    void initialize();
    
    bool virtual detected();
    
    bool virtual hasDetected();
};

#endif /* NGCustomObjectRecognizer_h */
