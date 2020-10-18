//
//  NGEngineControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 18.10.20.
//

#ifndef NGEngineControl_h
#define NGEngineControl_h

class NGEngineControl {
   
private:
    int _forwardPin;
    int _backwardPin;
    int _Speed;
    
public:
    NGEngineControl(int forwardPin, int backwardPin);
    
    void setSpeed(int Speed);
    
    void Run();
}

#endif /* NGEngineControl_h */
