//
//  NGLittleBigClockUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.04.25.
//

#ifndef NGLittleBigClockUnitControl_h
#define NGLittleBigClockUnitControl_h

#include <Arduino.h>
#include <NGCustomUnitControl.h>
#include <Specs/NGCustomWatchDial.h>

#define _VERSION "1.4"
#define VERSION (char*)_VERSION

#define DEFWATCHDELAY 1000

class NGLittleBigClockUnitControl : public NGCustomUnitControl {

private:
    long _lastRefresh = 0;
    bool _initWatchDial = false;
    NGCustomWatchDial *_watchDial = nullptr;

protected:
    void _create(char* name, byte address, int serialRate);
    
    void _processingReceivedData();
    
    void _processingStartupLoop();
    
    void _processingIRRemoteData();

public:
    NGLittleBigClockUnitControl();
    
    NGLittleBigClockUnitControl(char* name);
                  
    NGLittleBigClockUnitControl(char* name, byte address);
    
    NGLittleBigClockUnitControl(char* name, byte address, int serialRate);

    void registerWatchDial(NGCustomWatchDial *watchdial);

    void initialize();
    
    void processingLoop();

    void invalidWatchDial();
    
    void requestData(byte* data);
};

#endif /* NGLittleBigClockUnitControl_h */