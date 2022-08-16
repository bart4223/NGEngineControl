//
//  NGWirelessRemoteUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 13.08.22.
//

#ifndef NGWirelessRemoteUnitControl_h
#define NGWirelessRemoteUnitControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomUnitControl.h>

#define _VERSION "0.1"
#define VERSION (char*)_VERSION

class NGWirelessRemoteUnitControl : public NGCustomUnitControl {

protected:
    void _create(char* name, byte address, int serialRate);
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
    void _processingIRRemoteData();
    
public:
    NGWirelessRemoteUnitControl();
    
    NGWirelessRemoteUnitControl(char* name);
                  
    NGWirelessRemoteUnitControl(char* name, byte address);
    
    NGWirelessRemoteUnitControl(char* name, byte address, int serialRate);
    
    void initialize();
    
    void processingLoop();
    
    void requestData(byte* data);
};

#endif /* NGWirelessRemoteUnitControl_h */
