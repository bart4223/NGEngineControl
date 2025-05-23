//
//  NGCustomMotionControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 06.02.22.
//

#ifndef NGCustomMotionControl_h
#define NGCustomMotionControl_h

#include <Arduino.h>
#include <NGCommon.h>
#include <NGMotionSequenceStorage.h>
#include <NGCustomMotionMimic.h>
#include <NGCustomObjectRecognizer.h>

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
    NGMotionSequenceStorage *_motionSequenceStorage;
    NGCustomSteeringControl *_steeringControl;
    NGCustomMotionMimic *_motionMimic = nullptr;
    objectRecognizer _objectRecognizer[MAXOBECTRECOGNIZERCOUNT];
    int _objectRecognizerCount = 0;
    int _firedObjectRecognizer = -1;
    bool _logging = true;
    int _nextMotionSequence = NOCURRENTMOTIONSEQUENCE;
    
    virtual void _create(NGCustomSteeringControl *steeringControl);
    
    void _initializeMotionMimic();
    
    void _initializeObjectRecognizer();
    
    void _initializeSteering();
    
    void _processingObjectRecognizer();
    
public:
    void setMotionSequenceStorage(NGMotionSequenceStorage *storage);
    
    void setLogging(bool logging);
    
    bool getLogging();
    
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
    
    void clearNextMotionSequence();
    
    int getNextMotionSequence();
    
    virtual bool handleRemoteFunctionMenu(int currentmotionSequence);
    
    virtual bool handleRemoteFunctionOK(int currentmotionSequence);
    
    virtual bool handleRemoteFunctionPlay(int currentmotionSequence);

    virtual bool handleRemoteFunctionUp(int currentmotionSequence);
    
    virtual bool handleRemoteFunctionDown(int currentmotionSequence);
    
    virtual bool handleRemoteFunctionLeft(int currentmotionSequence);
    
    virtual bool handleRemoteFunctionRight(int currentmotionSequence);
};

#endif /* NGCustomMotionControl_h */
    
