//
//  NGMachineControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 13.05.21.
//

#ifndef NGMachineControl_h
#define NGMachineControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGEngineControl.h>
#include <NGJointControl.h>
#include <NGGripperControl.h>

class NGMachineControl {
    
public:
    NGMachineControl();
    
};

#endif /* NGMachineControl_h */
