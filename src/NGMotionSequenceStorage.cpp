//
//  NGMotionSequenceStorage.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 13.10.22.
//

#include <NGExceptionDefinitions.h>
#include "NGMotionSequenceStorage.h"

NGMotionSequenceStorage::NGMotionSequenceStorage() {
    _create();
}

void NGMotionSequenceStorage::_create() {
    
}

void NGMotionSequenceStorage::_raiseException(int id) {
    char error[100];
    _exceptionCount++;
    sprintf(error, "Ex %d(%d)", id, _exceptionCount);
    Serial.println(error);
}

byte NGMotionSequenceStorage::getSequenceCount() {
    return _count;
}

motionSequence NGMotionSequenceStorage::getSequence(byte sequence) {
    motionSequence res;
    if (sequence > _count) {
        _raiseException(ExceptionInvalidMotionSequenceIndex);
    } else {
        res = _sequences[sequence];
    }
    return res;
}

byte NGMotionSequenceStorage::getSequenceItemCount(byte sequence) {
    byte res;
    if (sequence > _count) {
        _raiseException(ExceptionInvalidMotionSequenceIndex);
    } else {
        res = _sequences[sequence].itemCount;
    }
    return res;
}

byte NGMotionSequenceStorage::addSequence(motionSequenceKind kind) {
    byte res = _count;
    if (_count < MAXMOTIONSEQUENCECOUNT) {
        motionSequence mss;
        mss.kind = kind;
        mss.itemCount = 0;
        _sequences[_count] = mss;
        _count++;
    } else {
        _raiseException(ExceptionTooMuchMotionSequenceCount);
    }
    return res;
}

void NGMotionSequenceStorage::addSequenceItem(byte motionSequence, byte speed, engineDirection direction, turnDirection turn, int duration, flashingLightSide light) {
    if (_sequences[motionSequence].itemCount < MAXMOTIONSEQUENCEITEMCOUNT) {
        motionSequenceItem msi;
        msi.speed = speed;
        msi.direction = direction;
        msi.turn = turn;
        msi.duration = duration;
        msi.light = light;
        _sequences[motionSequence].items[_sequences[motionSequence].itemCount] = msi;
        _sequences[motionSequence].itemCount++;
    } else {
        _raiseException(ExceptionTooMuchMotionSequenceItemCount);
    }
}
