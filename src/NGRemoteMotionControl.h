//
//  NGRemoteMotionControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.10.22.
//

#ifndef NGRemoteMotionControl_h
#define NGRemoteMotionControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomMotionControl.h>

class NGRemoteMotionControl : public NGCustomMotionControl {
  
protected:
    void _create(NGCustomSteeringControl *steeringControl);
    
public:
    NGRemoteMotionControl(NGCustomSteeringControl *steeringControl);
    
    bool handleRemoteFunctionMenu();
    
    bool handleRemoteFunctionOK();
    
    bool handleRemoteFunctionPlay();

    bool handleRemoteFunctionUp();
    
    bool handleRemoteFunctionDown();
    
    bool handleRemoteFunctionLeft();
    
    bool handleRemoteFunctionRight();
};

#endif /* NGRemoteMotionControl_h */
