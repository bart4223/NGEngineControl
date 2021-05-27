//
//  NGGripperControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.05.21.
//

#ifndef NGGripperControl_h
#define NGGripperControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGEngineControl.h>

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
    
    void release();
    
};
    
#endif /* NGGripperControl_h */
