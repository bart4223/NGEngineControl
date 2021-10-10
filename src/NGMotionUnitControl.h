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
#include <NGFlashingLight.h>

#define _VERSION "0.9"
#define VERSION (char*)_VERSION

#define DEFSTARTUPLOOPSCOUNT 3

#define MAXMOTIONSEQUENCECOUNT     5
#define MAXMOTIONSEQUENCEITEMCOUNT 3

enum flashingLightSide {flsNone, flsBoth, flsLeft, flsRight};

enum motionSequenceKind {mskStraight, mskLeft, mskRight};

struct motionSequenceItemStruct
{
    turnDirection turn;
    engineDirection direction;
    byte speed;
    flashingLightSide light;
    int duration; // milliseconds, 0 = infinite
};
typedef struct motionSequenceItemStruct motionSequenceItem;

struct motionSequenceStruct
{
    motionSequenceKind kind;
    motionSequenceItemStruct items[MAXMOTIONSEQUENCEITEMCOUNT];
    byte itemCount;
};
typedef struct motionSequenceStruct motionSequence;

class NGMotionUnitControl : public NGCustomUnitControl {

private:
    NGSteeringControl *_steeringControl;
    NGSoundMachine *_soundMachine;
    int _jingleStartup = -1;
    int _jingleStartupLoops = 0;
    NGLightSensor *_lightSensor = nullptr;
    NGFlashingLight *_flashingLightLeft = nullptr;
    NGFlashingLight *_flashingLightRight = nullptr;
    motionSequenceStruct _motionSequence[MAXMOTIONSEQUENCECOUNT];
    int _motionSequenceCount = 0;
    int _currentMotionSequence = -1;
    long int _currentMotionSequenceItemStarts = 0;
    byte _currentMotionSequenceItem = 0;

protected:
    void _create(char* name, byte address, int serialRate, int engineLeft, int engineRight, int offsetEngineLeft, int offsetEngineRight);
    
    void _processingReceivedData();
    
    void _playJingleStartup();
    
    void _processingLightSensor();
    
    void _processingStartupLoop();
    
    void _processingFlashingLights();
    
    void _processingMotionSequence();
    
    void _processingMotionSequenceItem(motionSequenceItem item);
    
public:
    NGMotionUnitControl();
    
    NGMotionUnitControl(char* name);
    
    NGMotionUnitControl(char* name, int offsetEngineLeft, int offsetEngineRight);
                  
    NGMotionUnitControl(char* name, byte address);
    
    NGMotionUnitControl(char* name, byte address, int serialRate);
    
    NGMotionUnitControl(char* name, byte address, int serialRate, int engineLeft, int engineRight);
    
    NGMotionUnitControl(char* name, byte address, int serialRate, int engineLeft, int engineRight, int offsetEngineLeft, int offsetEngineRight);

    void initialize();
    
    long int startUp();
    
    void registerStartup(int pinStartup, NGCustomJingle *jingle);
    
    void registerStartup(int pinStartup, NGCustomJingle *jingle, int loops);
    
    void registerLightSensor(NGLightSensor *lightSensor, int threshold, thresholdLevel level, byte pin, thresholdValence valence);
    
    void registerLightSensor(NGLightSensor *lightSensor, int threshold, thresholdLevel level, byte pin, thresholdValence valence, int delay);
    
    void registerFlashingLights(NGFlashingLight *flashingLightLeft, NGFlashingLight *flashingLightRight);
    
    byte registerMotionSequence(motionSequenceKind kind);
    
    void addMotionSequenceItemStop(byte motionSequence, int duration);
    
    void addMotionSequenceItem(byte motionSequence, byte speed, engineDirection direction, turnDirection turn);
    
    void addMotionSequenceItem(byte motionSequence, byte speed, engineDirection direction, turnDirection turn, int duration);
    
    void addMotionSequenceItem(byte motionSequence, byte speed, engineDirection direction, turnDirection turn, int duration, flashingLightSide light);
    
    void processingLoop();
    
    void requestData(byte* data);
    
    void setFlashingLight(flashingLightSide side, bool on);
    
    void setWarningLight(bool on);
};

#endif /* NGMotionUnitControl_h */
