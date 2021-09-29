//
//  NGMotionUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 28.09.21.
//

#ifndef NGMotionUnitControl_h
#define NGMotionUnitControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomUnitControl.h>
#include <NGSteeringControl.h>
#include <NGSoundMachine.h>
#include <NGCustomJingle.h>

#define _VERSION "0.2"
#define VERSION (char*)_VERSION

class NGMotionUnitControl : public NGCustomUnitControl {

private:
    NGSteeringControl *_steeringControl;
    NGSoundMachine *_soundMachine;
    int _jingleSplash = -1;
    
protected:
    void _create(char* name, byte address, int serialRate, int engineLeft, int engineRight);
    
    void _processingReceivedData();
    
    void _playJingleSplash();
    
public:
    NGMotionUnitControl();
    
    NGMotionUnitControl(char* name);
                  
    NGMotionUnitControl(char* name, byte address);
    
    NGMotionUnitControl(char* name, byte address, int serialRate);
    
    NGMotionUnitControl(char* name, byte address, int serialRate, int engineLeft, int engineRight);

    void initialize();
    
    void registerSplash(NGCustomJingle *jingle);
    
    void processingLoop();
    
    void requestData(byte* data);
};

#endif /* NGMotionUnitControl_h */
