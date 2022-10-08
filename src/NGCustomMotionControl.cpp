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

void NGCustomMotionControl::_initializeSteering() {
    _steeringControl->setLogging(_logging);
    _steeringControl->initialize();
    steeringStop();
}

void NGCustomMotionControl::_initializeObjectRecognizer() {
    for (int i = 0; i < _objectRecognizerCount; i++) {
        _objectRecognizer[i].recognizer->initialize();
        #ifdef NG_PLATFORM_MEGA
        char log[100];
        sprintf(log, "Object Recognizer \"%s\" initialized", _objectRecognizer[i].recognizer->getName());
        Serial.println(log);
        #endif
    }
}

void NGCustomMotionControl::_processingObjectRecognizer() {
    _firedObjectRecognizer = -1;
    for (int i = 0; i < _objectRecognizerCount; i++) {
        if (_objectRecognizer[i].recognizer->detected()) {
            _firedObjectRecognizer = i;
            break;
        }
    }
}

void NGCustomMotionControl::setLogging(bool logging) {
    _logging = logging;
}

bool NGCustomMotionControl::getLogging() {
    return _logging;
}

void NGCustomMotionControl::registerMotionMimic(NGCustomMotionMimic *mimic) {
    _motionMimic = mimic;
}

void NGCustomMotionControl::registerObjectRecognizer(NGCustomObjectRecognizer *recognizer) {
    registerObjectRecognizer(ormpNone, recognizer);
}

void NGCustomMotionControl::registerObjectRecognizer(objectRecognizerMountedPosition mounted, NGCustomObjectRecognizer *recognizer) {
    objectRecognizer objRec;
    objRec.mounted = mounted;
    objRec.recognizer = recognizer;
    _objectRecognizer[_objectRecognizerCount] = objRec;
    _objectRecognizerCount++;
}

int NGCustomMotionControl::getObjectRecognizerCount() {
    return _objectRecognizerCount;
}

bool NGCustomMotionControl::hasObjectRecognizer() {
    return _objectRecognizerCount > 0;
}

bool NGCustomMotionControl::hasFiredObjectRecognizer() {
    return _firedObjectRecognizer >= 0;
}

int NGCustomMotionControl::getFiredObjectRecognizerCloseness() {
    return _objectRecognizer[_firedObjectRecognizer].recognizer->getCloseness();
}

objectRecognizerMountedPosition NGCustomMotionControl::getFiredObjectRecognizerMountedPosition() {
    return _objectRecognizer[_firedObjectRecognizer].mounted;
}

bool NGCustomMotionControl::hasMotionMimic() {
    return _motionMimic != nullptr;
}

void NGCustomMotionControl::initialize() {
    _initializeSteering();
    _initializeMotionMimic();
    _initializeObjectRecognizer();
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

void NGCustomMotionControl::steeringRun(engineDirection direction, int speed) {
    _steeringControl->run(direction, speed);
}

void NGCustomMotionControl::steeringStop() {
    _steeringControl->stop();
}

void NGCustomMotionControl::steeringTurnForward(turnDirection turn) {
    _steeringControl->turnForward(turn);
}

void NGCustomMotionControl::steeringTurnBackward(turnDirection turn) {
    _steeringControl->turnBackward(turn);
}

void NGCustomMotionControl::steeringTurnForward(turnDirection turn, byte speed) {
    _steeringControl->turnForward(turn, speed);
}

void NGCustomMotionControl::steeringTurnBackward(turnDirection turn, byte speed) {
    _steeringControl->turnBackward(turn, speed);
}

void NGCustomMotionControl::processingLoop() {
    _processingObjectRecognizer();
}
