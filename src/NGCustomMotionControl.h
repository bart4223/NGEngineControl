//
//  NGCustomMotionControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 06.02.22.
//

#ifndef NGCustomMotionControl_h
#define NGCustomMotionControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCommon.h>
#include <NGCustomMotionMimic.h>
#include <NGCustomObjectRecognizer.h>
#include <NGCustomSteeringControl.h>

#ifdef NG_PLATFORM_MEGA
#define MAXOBECTRECOGNIZERCOUNT    10
#else
#define MAXOBECTRECOGNIZERCOUNT    3
#endif

enum objectRecognizerMountedPosition {ormpNone, ormpLeft, ormpRight, ormpFront, ormpBack};

struct objectRecognizerStruct
{
    objectRecognizerMountedPosition mounted;
    NGCustomObjectRecognizer *recognizer;
};
typedef struct objectRecognizerStruct objectRecognizer;

class NGCustomMotionControl {
  
protected:
    NGCustomSteeringControl *_steeringControl;
    NGCustomMotionMimic *_motionMimic = nullptr;
    objectRecognizer _objectRecognizer[MAXOBECTRECOGNIZERCOUNT];
    int _objectRecognizerCount = 0;
    int _firedObjectRecognizer = -1;

    virtual void _create(NGCustomSteeringControl *steeringControl);
    
    void _initializeMotionMimic();
    
    void _initializeObjectRecognizer();
    
    void _initializeSteering();

    void _processingObjectRecognizer();
    
public:
    void registerMotionMimic(NGCustomMotionMimic *mimic);
    
    void registerObjectRecognizer(NGCustomObjectRecognizer *recognizer);
    
    void registerObjectRecognizer(objectRecognizerMountedPosition mounted, NGCustomObjectRecognizer *recognizer);

    int getObjectRecognizerCount();
    
    bool hasObjectRecognizer();
    
    bool hasFiredObjectRecognizer();
    
    int getFiredObjectRecognizerCloseness();
    
    objectRecognizerMountedPosition getFiredObjectRecognizerMountedPosition();
    
    bool hasMotionMimic();

    void initialize();
    
    int thinkingDelay();
    
    bool nextMotionSequenceNecessary(int closeness);
    
    motionSequenceKind determineNextMotionSequenceKind(int closeness);
    
    bool correctNextMotionSequenceKind();
    
    void steeringRun(engineDirection direction, int speed);
    
    void steeringStop();

    void steeringTurnForward(turnDirection turn);
    
    void steeringTurnBackward(turnDirection turn);
    
    void steeringTurnForward(turnDirection turn, byte speed);
    
    void steeringTurnBackward(turnDirection turn, byte speed);

    void processingLoop();
};

#endif /* NGCustomMotionControl_h */
    
