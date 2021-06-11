//
//  NGCentralUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 11.06.21.
//

#ifndef NGCentralUnitControl_h
#define NGCentralUnitControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomUnitControl.h>

class NGCentralUnitControl : public NGCustomUnitControl {
    
public:
    NGCentralUnitControl();
    
    NGCentralUnitControl(char* name);
    
    NGCentralUnitControl(char* name, int serialRate);
    
    void initialize();
    
};

#endif /* NGCentralUnitControl_hpp */
