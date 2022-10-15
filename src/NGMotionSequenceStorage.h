//
//  NGMotionSequenceStorage.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 13.10.22.
//

#ifndef NGMotionSequenceStorage_h
#define NGMotionSequenceStorage_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCommon.h>
#include <NGCustomSteeringControl.h>

#ifdef NG_PLATFORM_MEGA
#define MAXMOTIONSEQUENCECOUNT     20
#define MAXMOTIONSEQUENCEITEMCOUNT 5
#else
#define MAXMOTIONSEQUENCECOUNT     6
#define MAXMOTIONSEQUENCEITEMCOUNT 4
#endif

enum motionSequenceKind {mskNone, mskStraight, mskLeft, mskRight, mskStop, mskBack, mskFullTurn};

enum flashingLightSide {flsNone, flsBoth, flsLeft, flsRight, flsBrake};

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

class NGMotionSequenceStorage {

private:
    motionSequence _sequences[MAXMOTIONSEQUENCECOUNT];
    byte _count = 0;
    int _exceptionCount = 0;
    
protected:
    void _create();
    
    void _raiseException(int id);
    
public:
    NGMotionSequenceStorage();
    
    byte getSequenceCount();
    
    motionSequence getSequence(byte sequence);
    
    byte getSequenceItemCount(byte sequence);
    
    byte addSequence(motionSequenceKind kind);
    
    void addSequenceItem(byte motionSequence, byte speed, engineDirection direction, turnDirection turn, int duration, flashingLightSide light);
};

#endif /* NGMotionSequenceStorage_h */
