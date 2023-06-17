//
//  NGBluetoothSlave.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 14.06.23.
//

#ifndef NGBluetoothSlave_h
#define NGBluetoothSlave_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGBluetooth.h"

typedef void (*bluetoothSlaveSwitchCallbackFunc)(byte context, bool on);
typedef void (*bluetoothSlaveCounterCallbackFunc)(byte context, int counter);

class NGBluetoothSlave {
    
private:
    bool _initialized = false;
    bool _logging = false;
    int _serialRate;
    int _currentIndex = 0;
    int _currentContext = BT_NO_CONTEXT;
    int _currentKind = BT_NO_KIND;
    bluetoothSlaveSwitchCallbackFunc _callbackSwitch = nullptr;
    bluetoothSlaveCounterCallbackFunc _callbackCounter = nullptr;
    
protected:
    void _create(int SerialRate);
    
    void _clearCurrent();
    
public:
    NGBluetoothSlave();
    
    NGBluetoothSlave(int SerialRate);
    
    void initialize();
    
    void setLogging(bool logging);
    
    bool getLogging();
    
    void registerSwitchCallback(bluetoothSlaveSwitchCallbackFunc callback);
    
    void registerCounterCallback(bluetoothSlaveCounterCallbackFunc callback);
    
    void processingLoop();
};

#endif /* NGBluetoothSlave_h */
