//
//  NGBluetoothRemoteUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 19.06.23.
//

#ifndef NGBluetoothRemoteUnitControl_h
#define NGBluetoothRemoteUnitControl_h

#include <Arduino.h>
#include <NGWirelessRemoteUnitControl.h>

#define _BTVERSION "0.1"
#define BTVERSION (char*)_BTVERSION

class NGBluetoothRemoteUnitControl : public NGWirelessRemoteUnitControl {

protected:
    void _create(char* name, byte address, int serialRate);

public:
    NGBluetoothRemoteUnitControl();
    
    NGBluetoothRemoteUnitControl(char* name);
                  
    NGBluetoothRemoteUnitControl(char* name, byte address);
    
    NGBluetoothRemoteUnitControl(char* name, byte address, int serialRate);
    
    void processingLoop();
};

#endif /* NGBluetoothRemoteUnitControl_h */
