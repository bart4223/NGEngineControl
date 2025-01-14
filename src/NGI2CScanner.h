//
//  NGI2CScanner.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 14.01.22.
//

#ifndef NGI2CScanner_h
#define NGI2CScanner_h

#include <Arduino.h>

#define DEFTIMEOUT 10000

class NGI2CScanner {

private:
    int _devices = 0;
    
protected:
    void _create();
    
    void _startScan();
    
    void _scan();
    
    void _finishScan();
    
public:
    NGI2CScanner();
    
    void scan();
    
    static void scanWire();
    
    static void scanWire(int timeout);
};

#endif /* NGI2CScanner_h */
