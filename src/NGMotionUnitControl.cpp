//
//  NGMotionUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 28.09.21.
//

#include "Wire.h"
#include "NGCommon.h"
#include "NGMemoryObserver.h"
#include "NGSteeringControl.h"
#include "NGMotionUnitControl.h"
#include "NGSimpleMotionControl.h"

NGMotionUnitControl::NGMotionUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE, new NGSimpleMotionControl(new NGSteeringControl(ENGINE_0, ENGINE_1, ENGINENULLOFFSET, ENGINENULLOFFSET)));
}

NGMotionUnitControl::NGMotionUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE, new NGSimpleMotionControl(new NGSteeringControl(ENGINE_0, ENGINE_1, ENGINENULLOFFSET, ENGINENULLOFFSET)));
}

NGMotionUnitControl::NGMotionUnitControl(char* name, NGCustomMotionControl *motionControl) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE, motionControl);
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address, NGCustomMotionControl *motionControl) {
    _create(name, address, DEFAULTSERIALRATE, motionControl);
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address, int serialRate, NGCustomMotionControl *motionControl) {
    _create(name, address, serialRate, motionControl);
}

void NGMotionUnitControl::_create(char* name, byte address, int serialRate, NGCustomMotionControl *motionControl) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    _motionControl = motionControl;
    if (_address == NOADDRESS) {
        Wire.begin();
    } else {
        Wire.begin(_address);
        Wire.onReceive(_unitWireReceiveEvent);
        Wire.onRequest(_unitWireRequestEvent);
    }
}

void NGMotionUnitControl::_initializeLightSensor() {
    if (_lightSensor != nullptr) {
        _lightSensor->initialize();
        #ifdef NG_PLATFORM_MEGA
        if (_logging) {
            char log[100];
            sprintf(log, "Light sensor initialized");
            writeInfo(log);
        }
        #endif
    }
}

void NGMotionUnitControl::_initializeFlashingLightLeft() {
    if (_flashingLightLeft != nullptr) {
        _flashingLightLeft->initialize();
        #ifdef NG_PLATFORM_MEGA
        if (_logging) {
            char log[100];
            sprintf(log, "Flashing light left initialized");
            writeInfo(log);
        }
        #endif
    }
}

void NGMotionUnitControl::_initializeFlashingLightRight() {
    if (_flashingLightRight != nullptr) {
        _flashingLightRight->initialize();
        #ifdef NG_PLATFORM_MEGA
        if (_logging) {
            char log[100];
            sprintf(log, "Flashing light right initialized");
            writeInfo(log);
        }
        #endif
    }
}

void NGMotionUnitControl::_initializeBrakeLight() {
    if (_brakeLightPin != -1) {
        pinMode(_brakeLightPin, OUTPUT);
    }
}

void NGMotionUnitControl::_initializeBackwardLight() {
    if (_backwardLightPin != -1) {
        pinMode(_backwardLightPin, OUTPUT);
    }
}

void NGMotionUnitControl::_initializeMotionControl() {
    _motionControl->initialize();
    #ifdef NG_PLATFORM_MEGA
    if (_logging) {
        char log[100];
        sprintf(log, "Motion Control initialized");
        writeInfo(log);
    }
    #endif
}

void NGMotionUnitControl::_initializeLaserCannon() {
    if (_laserCannon != nullptr) {
        _laserCannon->initialize();
        #ifdef NG_PLATFORM_MEGA
        if (_logging) {
            char log[100];
            sprintf(log, "Laser cannon initialized");
            writeInfo(log);
        }
        #endif
    }
}

void NGMotionUnitControl::_testSequenceStart() {
    if (_flashingLightLeft != nullptr) {
        _flashingLightLeft->testSequenceStart();
    }
    if (_flashingLightRight != nullptr) {
        _flashingLightRight->testSequenceStart();
    }
    if (_laserCannon != nullptr) {
        _laserCannon->testSequenceStart();
    }
    if (_brakeLightPin != -1) {
        _initializeBrakeLight();
        setBrakeLight(true);
    }
    if (_backwardLightPin != -1) {
        _initializeBackwardLight();
        setBackwardLight(true);
    }
    if (_lightSensor != nullptr) {
        _lightSensor->testSequenceStart();
    }
}

void NGMotionUnitControl::_testSequenceStop() {
    if (_flashingLightLeft != nullptr) {
        _flashingLightLeft->testSequenceStop();
    }
    if (_flashingLightRight != nullptr) {
        _flashingLightRight->testSequenceStop();
    }
    if (_laserCannon != nullptr) {
        _laserCannon->testSequenceStop();
    }
    if (_brakeLightPin != -1) {
        _initializeBrakeLight();
        setBrakeLight(false);
    }
    if (_backwardLightPin != -1) {
        _initializeBackwardLight();
        setBackwardLight(false);
    }
    if (_lightSensor != nullptr) {
        _lightSensor->testSequenceStop();
    }
}

void NGMotionUnitControl::_processingReceivedData() {
    
}

void NGMotionUnitControl::_resetCurrentMotionSequence() {
    _currentMotionSequence = -1;
    _currentMotionSequenceItem = 0;
    _currentMotionSequenceItemStarts = 0;
}

void NGMotionUnitControl::_playJingleBackward() {
    if (_jingleBackward != -1) {
        _playJingle(_jingleBackward);
    }
}

void NGMotionUnitControl::_playJingleThinking() {
    if (_jingleThinking != -1) {
        _playJingle(_jingleThinking);
    }
}

void NGMotionUnitControl::_laserCannonFireOn() {
    if (_laserCannon != nullptr) {
        _laserCannon->fireOn();
    }
}

void NGMotionUnitControl::_laserCannonFireOff() {
    if (_laserCannon != nullptr) {
        _laserCannon->fireOff();
    }
}

void NGMotionUnitControl::_processingStartupLoop() {
    _processingLightSensor();
}

void NGMotionUnitControl::_processingLightSensor() {
    if (_lightSensor != nullptr) {
        _lightSensor->determine();
    }
}

void NGMotionUnitControl::_processingFlashingLights() {
    if (_flashingLightLeft != nullptr) {
        _flashingLightLeft->processingLoop();
    }
    if (_flashingLightRight != nullptr) {
        _flashingLightRight->processingLoop();
    }
}

void NGMotionUnitControl::_processingMotionControl() {
    _motionControl->processingLoop();
}

void NGMotionUnitControl::_processingMotionSequence() {
    if (_currentMotionSequence == -1 || _motionControl->hasFiredObjectRecognizer()) {
        _determineCurrentMotionSequence();
    }
    if (_currentMotionSequence >= 0) {
        if (_currentMotionSequenceItem < _motionSequence[_currentMotionSequence].itemCount) {
            if (_currentMotionSequenceItemStarts == 0) {
                _currentMotionSequenceItemStarts = millis();
                _processingMotionSequenceItem(_motionSequence[_currentMotionSequence].items[_currentMotionSequenceItem]);
            } else {
                int duration = _motionSequence[_currentMotionSequence].items[_currentMotionSequenceItem].duration;
                if (duration != 0) {
                    if ((_currentMotionSequenceItemStarts + duration) < millis()) {
                        _currentMotionSequenceItem++;
                        _currentMotionSequenceItemStarts = 0;
                    }
                }
            }
            if (_motionSequence[_currentMotionSequence].items[_currentMotionSequenceItem].direction == edBackward) {
                setBackwardLight(true);
                _playJingleBackward();
            } else {
                setBackwardLight(false);
            }
        } else {
            _resetCurrentMotionSequence();
        }
    }
}

void NGMotionUnitControl::_processingMotionSequenceItem(motionSequenceItem item) {
    switch (item.turn) {
        case tdNone:
            if (item.direction == edNone) {
                _motionControl->steeringStop();
                int count = _motionControl->thinkingDelay();
                for (int i = 0; i < count; i++) {
                    _playJingleThinking();
                }
            } else {
                _motionControl->steeringRun(item.direction, item.speed);
            }
            break;
        case tdLeft:
        case tdLeftSoft:
        case tdRight:
        case tdRightSoft:
            if (item.direction == edForward) {
                _motionControl->steeringTurnForward(item.turn);
            } else if (item.direction == edBackward) {
                _motionControl->steeringTurnBackward(item.turn);
            }
            break;
    }
    if (item.light == flsNone) {
        setFlashingLight(flsBoth, false);
        setFlashingLight(flsBrake, false);
    } else {
        setFlashingLight(item.light, item.light != flsNone);
    }
}

void NGMotionUnitControl::_processingIRRemoteData() {
    char log[10];
    int index;
    for (int i = 0; i < _irremotefuncCount; i++) {
        if (_irremotefunc[i].protocol == _irremotedata.protocol && _irremotefunc[i].address == _irremotedata.address
                && _irremotefunc[i].command == _irremotedata.command) {
            switch (_irremotefunc[i].type) {
                case ftUp:
                    if (_currentMotionSequence !=  _getMotionSequenceByKind(mskStraight)) {
                        sprintf(log, "Go!");
                        index = _getMotionSequenceByKind(mskStraight);
                    } else {
                        sprintf(log, "Stop!");
                        index = _getMotionSequenceByKind(mskStop);
                    }
                    if (index != NOCURRENTMOTIONSEQUENCE) {
                        _resetCurrentMotionSequence();
                        _currentMotionSequence = index;
                        clearInfo();
                        writeInfo(log);
                    }
                    break;
                case ftDown:
                    if (_currentMotionSequence != _getMotionSequenceByKind(mskBack)) {
                        sprintf(log, "Back!");
                        index = _getMotionSequenceByKind(mskBack);
                    } else {
                        sprintf(log, "Stop!");
                        index = _getMotionSequenceByKind(mskStop);
                    }
                    if (index != NOCURRENTMOTIONSEQUENCE) {
                        _resetCurrentMotionSequence();
                        _currentMotionSequence = index;
                        clearInfo();
                        writeInfo(log);
                    }
                    break;
                case ftPlay:
                    index = _getMotionSequenceByKind(mskStop);
                    if (_currentMotionSequence != index && index != NOCURRENTMOTIONSEQUENCE) {
                        _currentMotionSequence = index;
                        _resetCurrentMotionSequence();
                        clearInfo();
                        sprintf(log, "Stop!");
                        writeInfo(log);
                    }
                    break;
            }
        }
    }
}

void NGMotionUnitControl::_determineCurrentMotionSequence() {
    bool newMotionSequence = true;
    if (_motionSequenceCount > 0) {
        if (_motionControl->hasMotionMimic()) {
            int closeness = NONECONTACT;
            if (_motionControl->hasFiredObjectRecognizer()) {
                closeness = _motionControl->getFiredObjectRecognizerCloseness();
                newMotionSequence = _motionControl->nextMotionSequenceNecessary(closeness);
            } else if (!_motionControl->hasObjectRecognizer()) {
                newMotionSequence = _motionControl->nextMotionSequenceNecessary(closeness);
            }
            if (newMotionSequence) {
                _resetCurrentMotionSequence();
                motionSequenceKind kind = _motionControl->determineNextMotionSequenceKind(closeness);
                if (_motionControl->hasFiredObjectRecognizer() && _motionControl->correctNextMotionSequenceKind()) {
                    switch(_motionControl->getFiredObjectRecognizerMountedPosition()) {
                        case ormpLeft:
                            if (kind == mskLeft) {
                                kind = mskRight;
                            }
                            break;
                        case ormpRight:
                            if (kind == mskRight) {
                                kind = mskLeft;
                            }
                            break;
                    }
                }
                for (int i = 0; i < _motionSequenceCount; i++) {
                    if (_motionSequence[i].kind == kind) {
                        _currentMotionSequence = i;
                        if (getYesOrNo()) {
                            break;
                        }
                    }
                }
            }
        } else if (_irremotefuncCount == 0) {
            _currentMotionSequence = random(0, _motionSequenceCount);
        }
    } else {
        _resetCurrentMotionSequence();
    }
    if (newMotionSequence) {
        if (_currentMotionSequence >= 0) {
            _currentMotionSequenceItem = 0;
            _currentMotionSequenceItemStarts = 0;
        } else {
            _playJingleAlarm();
        }
    }
}

void NGMotionUnitControl::_determineMotionInterruption() {
    char log[100];
    if (_motionInterruptionPin != -1) {
        if (!_motionInterrupted) {
            if (!digitalRead(_motionInterruptionPin)) {
                _motionInterrupted = true;
                _motionControl->steeringStop();
                beep();
                #ifdef NG_PLATFORM_MEGA
                clearInfo();
                sprintf(log, "Interruption!");
                writeInfo(log);
                #endif
                delay(DEFINTERRUPTIONDELAY);
            }
        } else if (!digitalRead(_motionInterruptionPin)) {
            beep();
            _motionInterrupted = false;
            _resetCurrentMotionSequence();
            #ifdef NG_PLATFORM_MEGA
            clearInfo();
            sprintf(log, "Go on...");
            writeInfo(log);
            #endif
            delay(DEFINTERRUPTIONDELAY);
        }
    }
}

int NGMotionUnitControl::_getMotionSequenceByKind(motionSequenceKind kind) {
    for (int i = 0; i < _motionSequenceCount; i++) {
        if (_motionSequence[i].kind == kind) {
            return i;
        }
    }
    return NOCURRENTMOTIONSEQUENCE;
}

void NGMotionUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    _initializeMotionControl();
    _initializeLightSensor();
    _initializeFlashingLightLeft();
    _initializeFlashingLightRight();
    _initializeBrakeLight();
    _initializeBackwardLight();
    _initializeLaserCannon();
    _initialized = true;
    if (_logging) {
        char log[100];
        sprintf(log, "...Unit \"%s\" with motion control initialized", _name);
        writeInfo(log);
    }
}

void NGMotionUnitControl::registerLightSensor(NGLightSensor *lightSensor, int threshold, thresholdLevel level, byte pin, thresholdValence valence) {
    registerLightSensor(lightSensor, threshold, level, pin, valence, 0);
}

void NGMotionUnitControl::registerLightSensor(NGLightSensor *lightSensor, int threshold, thresholdLevel level, byte pin, thresholdValence valence, int delay) {
    _lightSensor = lightSensor;
    _lightSensor->registerThreshold(threshold, level, pin, valence, delay);
}

void NGMotionUnitControl::registerFlashingLights(NGFlashingLight *flashingLightLeft, NGFlashingLight *flashingLightRight) {
    _flashingLightLeft = flashingLightLeft;
    _flashingLightRight = flashingLightRight;
}

void NGMotionUnitControl::registerBrakeLight(int brakeLightPin) {
    _brakeLightPin = brakeLightPin;
}

void NGMotionUnitControl::registerBackwardLight(int backwardLightPin) {
    _backwardLightPin = backwardLightPin;
}

void NGMotionUnitControl::registerMotionInterruption(int interruptionPin) {
    _motionInterruptionPin = interruptionPin;
}

byte NGMotionUnitControl::registerMotionSequence(motionSequenceKind kind) {
    byte res = _motionSequenceCount;
    if (_motionSequenceCount < MAXMOTIONSEQUENCECOUNT) {
        motionSequence mss;
        mss.kind = kind;
        mss.itemCount = 0;
        _motionSequence[_motionSequenceCount] = mss;
        _motionSequenceCount++;
    } else {
        _raiseException(ExceptionTooMuchMotionSequenceCount);
    }
    return res;
}

void NGMotionUnitControl::addMotionSequenceItemStop(byte motionSequence, int duration) {
    addMotionSequenceItemStop(motionSequence, duration, flsNone);
}

void NGMotionUnitControl::addMotionSequenceItemStop(byte motionSequence, int duration, flashingLightSide light) {
    addMotionSequenceItem(motionSequence, 0, edNone, tdNone, duration, light);
}

void NGMotionUnitControl::addMotionSequenceItem(byte motionSequence, byte speed, engineDirection direction, turnDirection turn) {
    addMotionSequenceItem(motionSequence, speed, direction, turn, 0);
}

void NGMotionUnitControl::addMotionSequenceItem(byte motionSequence, byte speed, engineDirection direction, turnDirection turn, int duration) {
    addMotionSequenceItem(motionSequence, speed, direction, turn, duration, flsNone);
}

void NGMotionUnitControl::addMotionSequenceItem(byte motionSequence, byte speed, engineDirection direction, turnDirection turn, int duration, flashingLightSide light) {
    if (_motionSequence[motionSequence].itemCount < MAXMOTIONSEQUENCEITEMCOUNT) {
        motionSequenceItem msi;
        msi.speed = speed;
        msi.direction = direction;
        msi.turn = turn;
        msi.duration = duration;
        msi.light = light;
        _motionSequence[motionSequence].items[_motionSequence[motionSequence].itemCount] = msi;
        _motionSequence[motionSequence].itemCount++;
    } else {
        _raiseException(ExceptionTooMuchMotionSequenceItemCount);
    }
}

void NGMotionUnitControl::registerJingleBackward(NGCustomJingle *jingle) {
    _jingleBackward = _registerJingle(jingle);
}

void NGMotionUnitControl::registerJingleThinking(NGCustomJingle *jingle) {
    _jingleThinking = _registerJingle(jingle);
}

void NGMotionUnitControl::registerMotionMimic(NGCustomMotionMimic *mimic) {
    _motionControl->registerMotionMimic(mimic);
}

void NGMotionUnitControl::registerObjectRecognizer(NGCustomObjectRecognizer *recognizer) {
    registerObjectRecognizer(ormpNone, recognizer);
}

void NGMotionUnitControl::registerObjectRecognizer(objectRecognizerMountedPosition mounted, NGCustomObjectRecognizer *recognizer) {
    if (_motionControl->getObjectRecognizerCount() < MAXOBECTRECOGNIZERCOUNT) {
        _motionControl->registerObjectRecognizer(mounted, recognizer);
    } else {
        _raiseException(ExceptionTooMuchObjectRecognizerCount);
    }
}

void NGMotionUnitControl::registerLaserCannon(NGLaserCannon *lasercannon) {
    _laserCannon = lasercannon;
}

void NGMotionUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    _processingLightSensor();
    _processingFlashingLights();
    _processingMotionControl();
    _determineMotionInterruption();
    if (!_motionInterrupted) {
        _processingMotionSequence();
    }
    switch (_workMode) {
        case wmNone:
            break;
        case wmObserveMemory:
            observeMemory(OBSERVEMEMORYDELAY);
            break;
        case wmSpec:
            observeMemory(OBSERVEMEMORYDELAY);
            break;
    }
}

void NGMotionUnitControl::requestData(byte* data) {
    
}

void NGMotionUnitControl::setFlashingLight(flashingLightSide side, bool on) {
    if (_flashingLightLeft != nullptr) {
        if (side == flsBoth || side == flsLeft) {
            _flashingLightLeft->setOn(on);
        }
    }
    if (_flashingLightRight != nullptr) {
        if (side == flsBoth || side == flsRight) {
            _flashingLightRight->setOn(on);
        }
    }
    if (_brakeLightPin != -1 && side == flsBrake) {
        setBrakeLight(on);
    }
}

void NGMotionUnitControl::setBrakeLight(bool on) {
    if (on) {
        digitalWrite(_brakeLightPin, HIGH);
    } else {
        digitalWrite(_brakeLightPin, LOW);
    }
}

void NGMotionUnitControl::setBackwardLight(bool on) {
    if (on) {
        digitalWrite(_backwardLightPin, HIGH);
    } else {
        digitalWrite(_backwardLightPin, LOW);
    }
}

void NGMotionUnitControl::setWarningLight(bool on) {
    setFlashingLight(flsBoth, on);
}

void NGMotionUnitControl::testSequenceStart() {
    _testSequenceStart();
}

void NGMotionUnitControl::testSequenceStop() {
    _testSequenceStop();
}

