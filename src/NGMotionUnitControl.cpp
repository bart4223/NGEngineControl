//
//  NGMotionUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 28.09.21.
//

#include "Wire.h"
#include "NGCommon.h"
#include "NGUnitControl.h"
#include "NGMemoryObserver.h"
#include "NGSteeringControl.h"
#include "NGMotionUnitControl.h"

NGMotionUnitControl::NGMotionUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE, new NGSteeringControl(ENGINE_0, ENGINE_1, ENGINENULLOFFSET, ENGINENULLOFFSET));
}

NGMotionUnitControl::NGMotionUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE, new NGSteeringControl(ENGINE_0, ENGINE_1, ENGINENULLOFFSET, ENGINENULLOFFSET));
}

NGMotionUnitControl::NGMotionUnitControl(char* name, int offsetEngineLeft, int offsetEngineRight) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE, new NGSteeringControl(ENGINE_0, ENGINE_1, offsetEngineLeft, offsetEngineRight));
}

NGMotionUnitControl::NGMotionUnitControl(char* name, int engineLeft, int engineRight, int offsetEngineLeft, int offsetEngineRight) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE, new NGSteeringControl(engineLeft, engineRight, offsetEngineLeft, offsetEngineRight));
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE, new NGSteeringControl(ENGINE_0, ENGINE_1, ENGINENULLOFFSET, ENGINENULLOFFSET));
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate, new NGSteeringControl(ENGINE_0, ENGINE_1, ENGINENULLOFFSET, ENGINENULLOFFSET));
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address, int serialRate, int engineLeft, int engineRight) {
    _create(name, address, serialRate, new NGSteeringControl(engineLeft, engineRight, ENGINENULLOFFSET, ENGINENULLOFFSET));
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address, int serialRate, int engineLeft, int engineRight, int offsetEngineLeft, int offsetEngineRight) {
    _create(name, address, serialRate, new NGSteeringControl(engineLeft, engineRight, offsetEngineLeft, offsetEngineRight));
}

NGMotionUnitControl::NGMotionUnitControl(char* name, NGSteeringControl *steeringControl) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE, steeringControl);
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address, NGSteeringControl *steeringControl) {
    _create(name, address, DEFAULTSERIALRATE, steeringControl);
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address, int serialRate, NGSteeringControl *steeringControl) {
    _create(name, address, serialRate, steeringControl);
}

void NGMotionUnitControl::_create(char* name, byte address, int serialRate, NGSteeringControl *steeringControl) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    _steeringControl = steeringControl;
    _soundMachine = new NGSoundMachine();
    if (_address == NOADDRESS) {
        Wire.begin();
    } else {
        Wire.begin(_address);
        Wire.onReceive(_unitWireReceiveEvent);
        Wire.onRequest(_unitWireRequestEvent);
    }
}

void NGMotionUnitControl::_initializeCore() {
    _initializeSoundMachine();
    _playJingleBoot();
    _initializeSteering();
    _steeringStop();
    #ifdef NG_PLATFORM_MEGA
    if (_logging) {
        writeInfo("Core initialized");
    }
    #endif
}

void NGMotionUnitControl::_initializeLightSensor() {
    if (_lightSensor != nullptr) {
        _lightSensor->initialize();
        #ifdef NG_PLATFORM_MEGA
        if (_logging) {
            writeInfo("Light sensor initialized");
        }
        #endif
    }
}

void NGMotionUnitControl::_initializeFlashingLightLeft() {
    if (_flashingLightLeft != nullptr) {
        _flashingLightLeft->initialize();
        #ifdef NG_PLATFORM_MEGA
        if (_logging) {
            writeInfo("Flashing light left initialized");
        }
        #endif
    }
}

void NGMotionUnitControl::_initializeFlashingLightRight() {
    if (_flashingLightRight != nullptr) {
        _flashingLightRight->initialize();
        #ifdef NG_PLATFORM_MEGA
        if (_logging) {
            writeInfo("Flashing light right initialized");
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

void NGMotionUnitControl::_initializeMotionMimic() {
    if (_motionMimic != nullptr) {
        _motionMimic->initialize();
        #ifdef NG_PLATFORM_MEGA
        if (_logging) {
            writeInfo("Mimic initialized");
        }
        #endif
    }
}

void NGMotionUnitControl::_initializeObjectRecognizer() {
    for (int i = 0; i < _objectRecognizerCount; i++) {
        _objectRecognizer[i].recognizer->initialize();
        #ifdef NG_PLATFORM_MEGA
        if (_logging) {
            char log[100];
            sprintf(log, "Object Recognizer \"%s\" initialized", _objectRecognizer[i].recognizer->getName());
            writeInfo(log);
        }
        #endif
    }
}

void NGMotionUnitControl::_initializeLaserCannon() {
    if (_laserCannon != nullptr) {
        _laserCannon->initialize();
        #ifdef NG_PLATFORM_MEGA
        if (_logging) {
            writeInfo("Laser cannon initialized");
        }
        #endif
    }
}

void NGMotionUnitControl::_initializeSoundMachine() {
    _soundMachine->initialize();
}

void NGMotionUnitControl::_initializeSteering() {
    _steeringControl->initialize();
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

void NGMotionUnitControl::_steeringStop() {
    _steeringControl->stop();
}

void NGMotionUnitControl::_resetCurrentMotionSequence() {
    _currentMotionSequence = -1;
}

int NGMotionUnitControl::_registerJingle(NGCustomJingle *jingle) {
    if (_soundMachine->getJingleCount() < _soundMachine->getMaxJingleCount()) {
        return _soundMachine->registerJingle(jingle);
    } else {
        _raiseException(ExceptionTooMuchJingleCount);
    }
    return -1;
}

void NGMotionUnitControl::_playJingle(byte jingle) {
    _soundMachine->play(jingle);
}

void NGMotionUnitControl::_playJingleBoot() {
    if (_jingleBoot != -1) {
        _playJingle(_jingleBoot);
    }
}

void NGMotionUnitControl::_playJingleBeep() {
    if (_jingleBeep != -1) {
        _playJingle(_jingleBeep);
    }
}
void NGMotionUnitControl::_playJingleStartup() {
    if (_jingleStartup != -1) {
        for (int i = 0; i < _jingleStartupLoops; i++) {
            _playJingle(_jingleStartup);
        }
    }
}

void NGMotionUnitControl::_playJingleBackward() {
    if (_jingleBackward != -1) {
        _playJingle(_jingleBackward);
    }
}

void NGMotionUnitControl::_playJingleAlarm() {
    if (_jingleAlarm != -1) {
        _playJingle(_jingleAlarm);
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

void NGMotionUnitControl::_processingObjectRecognizer() {
    _firedObjectRecognizer = -1;
    for (int i = 0; i < _objectRecognizerCount; i++) {
        if (_objectRecognizer[i].recognizer->detected()) {
            _firedObjectRecognizer = i;
            break;
        }
    }
}

void NGMotionUnitControl::_processingMotionSequence() {
    if (_currentMotionSequence == -1 || _firedObjectRecognizer != -1) {
        _determineCurrentMotionSequence();
    }
    if (_currentMotionSequence >= 0) {
        if (_currentMotionSequenceItem < _motionSequence[_currentMotionSequence].itemCount) {
            if (_currentMotionSequenceItemStarts == 0) {
                _currentMotionSequenceItemStarts = millis();
                _processingMotionSequenceItem(_motionSequence[_currentMotionSequence].items[_currentMotionSequenceItem]);
            } else {
                int duraction = _motionSequence[_currentMotionSequence].items[_currentMotionSequenceItem].duration;
                if (duraction != 0) {
                    if ((_currentMotionSequenceItemStarts + duraction) < millis()) {
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
                _steeringControl->stop();
                if (_motionMimic != nullptr) {
                    int count = _motionMimic->thinkingDelay();
                    for (int i = 0; i < count; i++) {
                        _playJingleThinking();
                    }
                }
            } else {
                _steeringControl->run(item.direction, item.speed);
            }
            break;
        case tdLeft:
        case tdLeftSoft:
        case tdRight:
        case tdRightSoft:
            if (item.direction == edForward) {
                _steeringControl->turnForward(item.turn);
            } else if (item.direction == edBackward) {
                _steeringControl->turnBackward(item.turn);
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

void NGMotionUnitControl::_determineCurrentMotionSequence() {
    bool newMotionSequence = true;
    if (_motionSequenceCount > 0) {
        if (_motionMimic != nullptr) {
            int closeness = NONECONTACT;
            if (_firedObjectRecognizer >= 0) {
                closeness = _objectRecognizer[_firedObjectRecognizer].recognizer->getCloseness();
                newMotionSequence = _motionMimic->nextMotionSequenceNecessary(closeness);
            } else if (_objectRecognizerCount == 0) {
                newMotionSequence = _motionMimic->nextMotionSequenceNecessary(closeness);
            }
            if (newMotionSequence) {
                _resetCurrentMotionSequence();
                motionSequenceKind kind = _motionMimic->determineNextMotionSequenceKind(closeness);
                if (_firedObjectRecognizer >= 0 && _motionMimic->correctNextMotionSequenceKind()) {
                    switch(_objectRecognizer[_firedObjectRecognizer].mounted) {
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
        } else {
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
    if (_motionInterruptionPin != -1) {
        if (!_motionInterrupted) {
            if (!digitalRead(_motionInterruptionPin)) {
                _motionInterrupted = true;
                _steeringStop();
                beep();
                #ifdef NG_PLATFORM_MEGA
                clearInfo();
                writeInfo("Interruption!");
                #endif
                delay(DEFINTERRUPTIONDELAY);
            }
        } else if (!digitalRead(_motionInterruptionPin)) {
            beep();
            _motionInterrupted = false;
            _resetCurrentMotionSequence();
            #ifdef NG_PLATFORM_MEGA
            clearInfo();
            writeInfo("Go on...");
            #endif
            delay(DEFINTERRUPTIONDELAY);
        }
    }
}

void NGMotionUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    _initializeCore();
    _initializeLightSensor();
    _initializeFlashingLightLeft();
    _initializeFlashingLightRight();
    _initializeBrakeLight();
    _initializeBackwardLight();
    _initializeMotionMimic();
    _initializeObjectRecognizer();
    _initializeLaserCannon();
    _initialized = true;
    if (_logging) {
        char log[100];
        sprintf(log, "...Unit \"%s\" with steering initialized", _name);
        writeInfo(log);
    }
    _writeState();
}

long int NGMotionUnitControl::startUp() {
    long int res = NGCustomUnitControl::startUp();
    _playJingleStartup();
    return res;
}

void NGMotionUnitControl::registerBoot(NGCustomJingle *jingle) {
    _jingleBoot = _registerJingle(jingle);
}

void NGMotionUnitControl::registerBeep(NGCustomJingle *jingle) {
    _jingleBeep = _registerJingle(jingle);
}

void NGMotionUnitControl::registerStartup(int pinStartup, NGCustomJingle *jingle) {
    registerStartup(pinStartup, jingle, DEFSTARTUPLOOPSCOUNT);
}

void NGMotionUnitControl::registerStartup(int pinStartup, NGCustomJingle *jingle, int loops) {
    NGCustomUnitControl::registerStartup(pinStartup);
    _jingleStartup = _registerJingle(jingle);
    _jingleStartupLoops = loops;
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

void NGMotionUnitControl::registerJingleAlarm(NGCustomJingle *jingle) {
    _jingleAlarm = _registerJingle(jingle);
}

void NGMotionUnitControl::registerJingleThinking(NGCustomJingle *jingle) {
    _jingleThinking = _registerJingle(jingle);
}

void NGMotionUnitControl::registerMotionMimic(NGCustomMotionMimic *mimic) {
    _motionMimic = mimic;
}

void NGMotionUnitControl::registerObjectRecognizer(NGCustomObjectRecognizer *recognizer) {
    registerObjectRecognizer(ormpNone, recognizer);
}

void NGMotionUnitControl::registerObjectRecognizer(objectRecognizerMountedPosition mounted, NGCustomObjectRecognizer *recognizer) {
    if (_objectRecognizerCount < MAXOBECTRECOGNIZERCOUNT) {
        objectRecognizer objRec;
        objRec.mounted = mounted;
        objRec.recognizer = recognizer;
        _objectRecognizer[_objectRecognizerCount] = objRec;
        _objectRecognizerCount++;
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
    _processingObjectRecognizer();
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

void NGMotionUnitControl::beep() {
    _playJingleBeep();
}

void NGMotionUnitControl::testSequenceStart() {
    _testSequenceStart();
}

void NGMotionUnitControl::testSequenceStop() {
    _testSequenceStop();
}

