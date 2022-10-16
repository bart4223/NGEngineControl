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
    motionSequenceItem items[MAXMOTIONSEQUENCEITEMCOUNT];
    byte itemCount;
};
typedef struct motionSequenceStruct motionSequence;

class NGMotionSequenceStorage {

private:
    motionSequence _sequences[MAXMOTIONSEQUENCECOUNT];
    byte _count = 0;
    int _exceptionCount = 0;
    bool _logging = false;
    bool _initialized = false;
    
protected:
    void _create();
    
    void _raiseException(int id);
    
public:
    NGMotionSequenceStorage();
    
    void initialize();
    
    void setLogging(bool logging);
    
    byte getSequenceCount();
    
    motionSequenceKind getSequenceKind(byte sequence);
    
    byte getSequenceItemCount(byte sequence);
    
    turnDirection getSequenceItemTurnDirection(byte sequence, byte item);
    
    engineDirection getSequenceItemEngineDirection(byte sequence, byte item);
    
    byte getSequenceItemSpeed(byte sequence, byte item);
    
    int getSequenceItemDuration(byte sequence, byte item);
    
    flashingLightSide getSequenceItemLight(byte sequence, byte item);
    
    byte addSequence(motionSequenceKind kind);
    
    void addSequenceItem(byte motionSequence, byte speed, engineDirection direction, turnDirection turn, int duration, flashingLightSide light);
};

#endif /* NGMotionSequenceStorage_h */
