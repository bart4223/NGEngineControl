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

#ifdef NG_PLATFORM_MEGA
#define MAXMOTIONSEQUENCECOUNT     20
#define MAXMOTIONSEQUENCEITEMCOUNT 5
#else
#define MAXMOTIONSEQUENCECOUNT     6
#define MAXMOTIONSEQUENCEITEMCOUNT 4
#endif

#include <NGCustomSteeringControl.h>

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

#endif /* NGMotionSequenceStorage_h */
