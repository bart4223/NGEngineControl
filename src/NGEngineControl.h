//
//  NGEngineControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 18.10.20.
//

#ifndef NGEngineControl_h
#define NGEngineControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

enum direction { FORWARD, BACKWARD };

class NGEngineControl {
   
private:
    int _forwardPin;
    int _backwardPin;
    int _speed;
    bool _initialized;
    
public:
    NGEngineControl(int forwardPin, int backwardPin);
    
    void initialize();
    
    void setSpeed(int speed);
    
    bool run(direction direction);
};

#endif /* NGEngineControl_h */
