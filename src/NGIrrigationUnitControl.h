//
//  NGIrrigationUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.03.22.
//

#ifndef NGIrrigationUnitControl_h
#define NGIrrigationUnitControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomUnitControl.h>
#include <NGPumpControl.h>

#define _VERSION "0.1"
#define VERSION (char*)_VERSION

#define MAXPUMPCOUNT 3

class NGIrrigationUnitControl : public NGCustomUnitControl {

private:
    NGPumpControl *_pumps[MAXPUMPCOUNT];
    int _pumpCount = 0;
    
protected:
    void _create(char* name, byte address, int serialRate);

    void _initializePumps();
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
public:
    NGIrrigationUnitControl();
    
    NGIrrigationUnitControl(char* name);
                  
    NGIrrigationUnitControl(char* name, byte address);
    
    NGIrrigationUnitControl(char* name, byte address, int serialRate);

    void initialize();
    
    void registerPump(byte pinPump);

    void processingLoop();
    
    void requestData(byte* data);
};

#endif /* NGIrrigationUnitControl_h */
