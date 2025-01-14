//
//  NGMotionUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 28.09.21.
//

#ifndef NGMotionUnitControl_h
#define NGMotionUnitControl_h

#include <Arduino.h>
#include <NGCommon.h>
#include <NGExceptionDefinitions.h>
#include <NGMotionSequenceStorage.h>
#include <NGCustomUnitControl.h>
#include <NGCustomMotionControl.h>
#include <NGCustomMotionMimic.h>
#include <NGCustomJingle.h>
#include <NGLightSensor.h>
#include <NGFlashingLight.h>
#include <NGLaserCannon.h>

#define _VERSION "6.2"
#define VERSION (char*)_VERSION

#define DEFINTERRUPTIONDELAY 1000

class NGMotionUnitControl : public NGCustomUnitControl, NGITestableComponent {

private:
    NGMotionSequenceStorage *_motionSequenceStorage;
    NGCustomMotionControl *_motionControl;
    NGLightSensor *_lightSensor = nullptr;
    NGFlashingLight *_flashingLightLeft = nullptr;
    NGFlashingLight *_flashingLightRight = nullptr;
    NGLaserCannon *_laserCannon = nullptr;
    bool _motionInterrupted = false;
    int _motionInterruptionPin = -1;
    int _brakeLightPin = -1;
    int _backwardLightPin = -1;
    int _jingleBackward = -1;
    int _jingleThinking = -1;
    int _currentMotionSequence = NOCURRENTMOTIONSEQUENCE;
    long int _currentMotionSequenceItemStarts = 0;
    byte _currentMotionSequenceItem = 0;
    int _lastInfoID = -1;

protected:
    void _create(char* name, byte address, int serialRate, NGCustomMotionControl *motionControl);
    
    void _initializeLightSensor();
    
    void _initializeFlashingLightLeft();
    
    void _initializeFlashingLightRight();
    
    void _initializeBrakeLight();
    
    void _initializeBackwardLight();
    
    void _initializeMotionControl();
    
    void _initializeMotionSequenceStorage();
    
    void _initializeLaserCannon();
    
    void _testSequenceStart();
    
    void _testSequenceStop();
    
    void _processingReceivedData();
    
    void _resetCurrentMotionSequence();
       
    void _playJingleBackward();
    
    void _playJingleThinking();
    
    void _laserCannonFireOn();
    
    void _laserCannonFireOff();
    
    void _processingLightSensor();
    
    void _processingStartupLoop();
    
    void _processingFlashingLights();
    
    void _processingMotionControl();
    
    void _processingMotionSequence();
    
    void _processingCurrentMotionSequenceItem();
    
    void _processingIRRemoteData();
    
    void _determineCurrentMotionSequence();
    
    void _determineMotionInterruption();
    
    int _getMotionSequenceByKind(motionSequenceKind kind, int currentmotionSequence);
    
public:
    NGMotionUnitControl();
    
    NGMotionUnitControl(char* name);
    
    NGMotionUnitControl(char* name, NGCustomMotionControl *motionControl);
    
    NGMotionUnitControl(char* name, byte address, NGCustomMotionControl *motionControl);
    
    NGMotionUnitControl(char* name, byte address, int serialRate, NGCustomMotionControl *motionControl);

    void initialize();
    
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
    
    void registerJingleThinking(NGCustomJingle *jingle);
    
    void registerMotionMimic(NGCustomMotionMimic *mimic);
    
    void registerObjectRecognizer(NGCustomObjectRecognizer *recognizer);
    
    void registerObjectRecognizer(objectRecognizerMountedPosition mounted, NGCustomObjectRecognizer *recognizer);
    
    void registerLaserCannon(NGLaserCannon *lasercannon);
    
    void processingLoop();
    
    void requestData(byte* data);
    
    void setFlashingLight(flashingLightSide side, bool on);
    
    void setBrakeLight(bool on);
    
    void setBackwardLight(bool on);
    
    void setWarningLight(bool on);
    
    void testSequenceStart();
    
    void testSequenceStop();
};

#endif /* NGMotionUnitControl_h */
