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

void NGMotionSequenceStorage::_raiseExceptionWithIndex(int id, byte index) {
    char error[100];
    _exceptionCount++;
    sprintf(error, "Ex %d(%d)/%d", id, _exceptionCount, index);
    Serial.println(error);
}

motionSequence NGMotionSequenceStorage::_getSequence(byte sequence) {
    motionSequence res;
    if (sequence >= _count) {
        _raiseExceptionWithIndex(ExceptionInvalidMotionSequenceIndex, sequence);
    } else {
        res = _sequences[sequence];
    }
    return res;
}

motionSequenceItem NGMotionSequenceStorage::_getSequenceItem(byte sequence, byte item) {
    motionSequenceItem res;
    if (sequence >= _count) {
        _raiseExceptionWithIndex(ExceptionInvalidMotionSequenceIndex, sequence);
    } else {
        if (item >= _sequences[sequence].itemCount) {
            _raiseExceptionWithIndex(ExceptionInvalidMotionSequenceItemIndex, item);
        } else {
            res = _sequences[sequence].items[item];
        }
    }
    return res;
}

void NGMotionSequenceStorage::initialize() {
    _initialized = true;
}

void NGMotionSequenceStorage::setLogging(bool logging) {
    _logging = logging;
}

byte NGMotionSequenceStorage::getSequenceCount() {
    return _count;
}

motionSequenceKind NGMotionSequenceStorage::getSequenceKind(byte sequence) {
    return _getSequence(sequence).kind;
}

byte NGMotionSequenceStorage::getSequenceItemCount(byte sequence) {
    return _getSequence(sequence).itemCount;
}

turnDirection NGMotionSequenceStorage::getSequenceItemTurnDirection(byte sequence, byte item) {
    return _getSequenceItem(sequence, item).turn;
}

engineDirection NGMotionSequenceStorage::getSequenceItemEngineDirection(byte sequence, byte item) {
    return _getSequenceItem(sequence, item).direction;
}

byte NGMotionSequenceStorage::getSequenceItemSpeed(byte sequence, byte item) {
    return _getSequenceItem(sequence, item).speed;
}

int NGMotionSequenceStorage::getSequenceItemDuration(byte sequence, byte item) {
    return _getSequenceItem(sequence, item).duration;
}

flashingLightSide NGMotionSequenceStorage::getSequenceItemLight(byte sequence, byte item) {
    return _getSequenceItem(sequence, item).light;
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
