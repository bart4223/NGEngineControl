//
//  NGGripperControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.05.21.
//

#ifndef NGGripperControl_h
#define NGGripperControl_h

#include <Arduino.h>
#include <NGEngineControl.h>

#define DEFAULTGRIPDELAYONE      900
#define DEFAULTGRIPDELAYTWO     3000
#define DEFAULTRELEASEDELAYONE   900
#define DEFAULTRELEASEDELAYTWO  1600

#define SIMULATEDELAY 250

class NGGripperControl {

private:
    bool _initialized;
    bool _logging;
    int _minSpeed;
    int _maxSpeed;
    NGEngineControl _engine = NGEngineControl();

protected:
    void _create(int engine, int serialRate);
  
public:
    NGGripperControl();
    
    NGGripperControl(int engine);
    
    NGGripperControl(int engine, int serialRate);
    
    void initialize(int minSpeed, int maxSpeed);

    void grip();
    
    void grip(unsigned long delayOne, unsigned long delayTwo);
    
    void release();
    
    void release(unsigned long delayOne, unsigned long delayTwo);
    
    void simulate();
    
};
    
#endif /* NGGripperControl_h */
