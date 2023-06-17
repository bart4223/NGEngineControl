//
//  NGBluetoothMaster.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 12.06.23.
//

#ifndef NGBluetoothMaster_h
#define NGBluetoothMaster_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class NGBluetoothMaster {
    
private:
    bool _initialized = false;
    int _serialRate;
    
protected:
    void _create(int SerialRate);
    
    void _sendHeader();
    
    void _sendKindSoundCheck();

    void _sendKindSwitch();
    
    void _sendKindCounter();
    
public:
    NGBluetoothMaster();
    
    NGBluetoothMaster(int SerialRate);
    
    void initialize();
    
    void sendSoundcheck();
    
    void sendSwitchCommand(byte context, bool on);
    
    void sendCounterCommand(byte context, int counter);
};

#endif /* NGBluetoothMaster_h */
