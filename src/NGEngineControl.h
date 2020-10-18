//
//  NGEngineControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 18.10.20.
//

#ifndef NGEngineControl_h
#define NGEngineControl_h

enum direction { FORWARD, BACKWARD };

class NGEngineControl {
   
private:
    int _forwardPin;
    int _backwardPin;
    int _speed;
    
public:
    NGEngineControl(int forwardPin, int backwardPin);
    
    void setSpeed(int speed);
    
    void run(direction direction);
};

#endif /* NGEngineControl_h */
