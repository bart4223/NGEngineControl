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
#include <NGLightSensor.h>

#define _VERSION "0.3"
#define VERSION (char*)_VERSION

#define DEFSTARTUPLOOPSCOUNT 3

class NGMotionUnitControl : public NGCustomUnitControl {

private:
    NGSteeringControl *_steeringControl;
    NGSoundMachine *_soundMachine;
    int _jingleStartup = -1;
    int _jingleStartupLoops = 0;
    NGLightSensor *_lightSensor = nullptr;
    
protected:
    void _create(char* name, byte address, int serialRate, int engineLeft, int engineRight);
    
    void _processingReceivedData();
    
    void _playJingleStartup();
    
    void _processingLightSensor();
    
    void _processingStartupLoop();
    
public:
    NGMotionUnitControl();
    
    NGMotionUnitControl(char* name);
                  
    NGMotionUnitControl(char* name, byte address);
    
    NGMotionUnitControl(char* name, byte address, int serialRate);
    
    NGMotionUnitControl(char* name, byte address, int serialRate, int engineLeft, int engineRight);

    void initialize();
    
    void startUp();
    
    void registerStartup(int pinStartup, NGCustomJingle *jingle);
    
    void registerStartup(int pinStartup, NGCustomJingle *jingle, int loops);
    
    void registerLightSensor(NGLightSensor *lightSensor, int threshold, thresholdLevel level, byte pin, thresholdValence valence);
    
    void registerLightSensor(NGLightSensor *lightSensor, int threshold, thresholdLevel level, byte pin, thresholdValence valence, int delay);
    
    void processingLoop();
    
    void requestData(byte* data);
};

#endif /* NGMotionUnitControl_h */
