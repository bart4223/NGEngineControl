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

#include <NGCommon.h>
#include <NGCustomUnitControl.h>
#include <NGSteeringControl.h>
#include <NGSoundMachine.h>
#include <NGCustomJingle.h>
#include <NGLightSensor.h>
#include <NGFlashingLight.h>
#include <NGLaserCannon.h>
#include <NGCustomMotionMimic.h>
#include <NGCustomObjectRecognizer.h>

#define _VERSION "3.2"
#define VERSION (char*)_VERSION

#define DEFSTARTUPLOOPSCOUNT    3
#define DEFINTERRUPTIONDELAY 1000

#ifdef NG_PLATFORM_MEGA
#define MAXMOTIONSEQUENCECOUNT     20
#define MAXMOTIONSEQUENCEITEMCOUNT 5
#define MAXOBECTRECOGNIZERCOUNT    10
#else
#define MAXMOTIONSEQUENCECOUNT     6
#define MAXMOTIONSEQUENCEITEMCOUNT 4
#define MAXOBECTRECOGNIZERCOUNT    3
#endif

#define ExceptionTooMuchJingleCount             300
#define ExceptionTooMuchObjectRecognizerCount   301
#define ExceptionTooMuchMotionSequenceCount     302
#define ExceptionTooMuchMotionSequenceItemCount 303

enum objectRecognizerMountedPosition {ormpNone, ormpLeft, ormpRight, ormpFront, ormpBack};
enum flashingLightSide {flsNone, flsBoth, flsLeft, flsRight, flsBrake};

struct objectRecognizerStruct
{
    objectRecognizerMountedPosition mounted;
    NGCustomObjectRecognizer *recognizer;
};
typedef struct objectRecognizerStruct objectRecognizer;

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
    int _jingleBackward = -1;
    int _jingleAlarm = -1;
    int _jingleThinking = -1;
    int _jingleBoot = -1;
    int _jingleBeep = -1;
    NGLightSensor *_lightSensor = nullptr;
    NGFlashingLight *_flashingLightLeft = nullptr;
    NGFlashingLight *_flashingLightRight = nullptr;
    motionSequence _motionSequence[MAXMOTIONSEQUENCECOUNT];
    int _motionSequenceCount = 0;
    int _currentMotionSequence = -1;
    long int _currentMotionSequenceItemStarts = 0;
    byte _currentMotionSequenceItem = 0;
    int _brakeLightPin = -1;
    int _backwardLightPin = -1;
    NGCustomMotionMimic *_motionMimic = nullptr;
    objectRecognizer _objectRecognizer[MAXOBECTRECOGNIZERCOUNT];
    int _objectRecognizerCount = 0;
    int _firedObjectRecognizer = -1;
    bool _motionInterrupted = false;
    int _motionInterruptionPin = -1;
    NGLaserCannon *_laserCannon = nullptr;

protected:
    void _create(char* name, byte address, int serialRate, int engineLeft, int engineRight, int offsetEngineLeft, int offsetEngineRight);
    
    void _initializeCore();
    
    void _initializeStreering();

    void _initializeSoundMachine();
    
    void _processingReceivedData();
    
    void _steeringStop();
    
    void _resetCurrentMotionSequence();
    
    int _registerJingle(NGCustomJingle *jingle);
    
    void _playJingle(byte jingle);
    
    void _playJingleBoot();
    
    void _playJingleBeep();
    
    void _playJingleStartup();
    
    void _playJingleBackward();
    
    void _playJingleAlarm();
    
    void _playJingleThinking();
    
    void _laserCannonFireOn();
    
    void _laserCannonFireOff();
    
    void _processingLightSensor();
    
    void _processingStartupLoop();
    
    void _processingFlashingLights();
    
    void _processingObjectRecognizer();
    
    void _processingMotionSequence();
    
    void _processingMotionSequenceItem(motionSequenceItem item);
    
    void _determineCurrentMotionSequence();
    
    void _determineMotionInterruption();
    
public:
    NGMotionUnitControl();
    
    NGMotionUnitControl(char* name);
    
    NGMotionUnitControl(char* name, int offsetEngineLeft, int offsetEngineRight);
                  
    NGMotionUnitControl(char* name, int engineLeft, int engineRight, int offsetEngineLeft, int offsetEngineRight);
    
    NGMotionUnitControl(char* name, byte address);
    
    NGMotionUnitControl(char* name, byte address, int serialRate);
    
    NGMotionUnitControl(char* name, byte address, int serialRate, int engineLeft, int engineRight);
    
    NGMotionUnitControl(char* name, byte address, int serialRate, int engineLeft, int engineRight, int offsetEngineLeft, int offsetEngineRight);

    void initialize();
    
    long int startUp();
    
    void registerBoot(NGCustomJingle *jingle);
    
    void registerBeep(NGCustomJingle *jingle);
    
    void registerStartup(int pinStartup, NGCustomJingle *jingle);
    
    void registerStartup(int pinStartup, NGCustomJingle *jingle, int loops);
    
    void registerLightSensor(NGLightSensor *lightSensor, int threshold, thresholdLevel level, byte pin, thresholdValence valence);
    
    void registerLightSensor(NGLightSensor *lightSensor, int threshold, thresholdLevel level, byte pin, thresholdValence valence, int delay);
    
    void registerFlashingLights(NGFlashingLight *flashingLightLeft, NGFlashingLight *flashingLightRight);
    
    void registerBrakeLight(int brakeLightPin);
    
    void registerBackwardLight(int brakeLightPin);
    
    void registerMotionInterruption(int interruptionPin);
    
    byte registerMotionSequence(motionSequenceKind kind);
    
    void addMotionSequenceItemStop(byte motionSequence, int duration);
    
    void addMotionSequenceItemStop(byte motionSequence, int duration, flashingLightSide light);
    
    void addMotionSequenceItem(byte motionSequence, byte speed, engineDirection direction, turnDirection turn);
    
    void addMotionSequenceItem(byte motionSequence, byte speed, engineDirection direction, turnDirection turn, int duration);
    
    void addMotionSequenceItem(byte motionSequence, byte speed, engineDirection direction, turnDirection turn, int duration, flashingLightSide light);
    
    void registerJingleBackward(NGCustomJingle *jingle);
    
    void registerJingleAlarm(NGCustomJingle *jingle);
    
    void registerJingleThinking(NGCustomJingle *jingle);
    
    void registerMotionMimic(NGCustomMotionMimic *mimic);
    
    void registerObjectRecognizer(NGCustomObjectRecognizer *recognizer);
    
    void registerObjectRecognizer(objectRecognizerMountedPosition mounted, NGCustomObjectRecognizer *recognizer);
    
    void registerLaserCannon(NGLaserCannon *lasercannon);
    
    void processingLoop();
    
    void requestData(byte* data);
    
    void setFlashingLight(flashingLightSide side, bool on);
    
    void setWarningLight(bool on);
    
    void beep();
};

#endif /* NGMotionUnitControl_h */
