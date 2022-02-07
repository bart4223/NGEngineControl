//
//  NGCustomMotionControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 06.02.22.
//

#include "NGCustomMotionControl.h"

void NGCustomMotionControl::_initializeMotionMimic() {
    if (hasMotionMimic()) {
        _motionMimic->initialize();
        #ifdef NG_PLATFORM_MEGA
        char log[100];
        sprintf(log, "Mimic \"%s\" initialized", _motionMimic->getName());
        Serial.println(log);
        #endif
    }
}

void NGCustomMotionControl::registerMotionMimic(NGCustomMotionMimic *mimic) {
    _motionMimic = mimic;
}

bool NGCustomMotionControl::hasMotionMimic() {
    return _motionMimic != nullptr;
}

void NGCustomMotionControl::initialize() {
    _initializeMotionMimic();
}

int NGCustomMotionControl::thinkingDelay() {
    int res = 0;
    if (hasMotionMimic()) {
        res = _motionMimic->thinkingDelay();
    }
    return res;
}

bool NGCustomMotionControl::nextMotionSequenceNecessary(int closeness) {
    bool res = false;
    if (hasMotionMimic()) {
        res = _motionMimic->nextMotionSequenceNecessary(closeness);
    }
    return res;
}

motionSequenceKind NGCustomMotionControl::determineNextMotionSequenceKind(int closeness) {
    motionSequenceKind res = mskNone;
    if (hasMotionMimic()) {
        res = _motionMimic->determineNextMotionSequenceKind(closeness);
    }
    return res;
}

bool NGCustomMotionControl::correctNextMotionSequenceKind() {
    bool res = false;
    if (hasMotionMimic()) {
        res = _motionMimic->correctNextMotionSequenceKind();
    }return res;
}
