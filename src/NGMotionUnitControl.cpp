//
//  NGMotionUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 28.09.21.
//

#include "NGCommon.h"
#include "NGMemoryObserver.h"
#include "NGSteeringControl.h"
#include "NGMotionUnitControl.h"

NGMotionUnitControl::NGMotionUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE, ENGINE_0, ENGINE_1, ENGINENULLOFFSET, ENGINENULLOFFSET);
}

NGMotionUnitControl::NGMotionUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE, ENGINE_0, ENGINE_1, ENGINENULLOFFSET, ENGINENULLOFFSET);
}

NGMotionUnitControl::NGMotionUnitControl(char* name, int offsetEngineLeft, int offsetEngineRight) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE, ENGINE_0, ENGINE_1, offsetEngineLeft, offsetEngineRight);
}

NGMotionUnitControl::NGMotionUnitControl(char* name, int engineLeft, int engineRight, int offsetEngineLeft, int offsetEngineRight) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE, engineLeft, engineRight, offsetEngineLeft, offsetEngineRight);
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE, ENGINE_0, ENGINE_1, ENGINENULLOFFSET, ENGINENULLOFFSET);
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate, ENGINE_0, ENGINE_1, ENGINENULLOFFSET, ENGINENULLOFFSET);
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address, int serialRate, int engineLeft, int engineRight) {
    _create(name, address, serialRate, engineLeft, engineRight, ENGINENULLOFFSET, ENGINENULLOFFSET);
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address, int serialRate, int engineLeft, int engineRight, int offsetEngineLeft, int offsetEngineRight) {
    _create(name, address, serialRate, engineLeft, engineRight, offsetEngineLeft, offsetEngineRight);
}

void NGMotionUnitControl::_create(char* name, byte address, int serialRate, int engineLeft, int engineRight, int offsetEngineLeft, int offsetEngineRight) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    _steeringControl = new NGSteeringControl(engineLeft, engineRight, offsetEngineLeft, offsetEngineRight);
    _soundMachine = new NGSoundMachine();
}

void NGMotionUnitControl::_processingReceivedData() {
    
}

void NGMotionUnitControl::_playJingle(byte jingle) {
    _soundMachine->play(jingle);
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
            _currentMotionSequence = -1;
            _firedObjectRecognizer = i;
            break;
        }
    }
}

void NGMotionUnitControl::_processingMotionSequence() {
    if (_currentMotionSequence == -1) {
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
                _playJingleBackward();
            }
        } else {
            _currentMotionSequence = -1;
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
    _currentMotionSequence = -1;
    if (_motionSequenceCount > 0) {
        if (_motionMimic != nullptr) {
            int closeness = NONECONTACT;
            if (_firedObjectRecognizer >= 0) {
                closeness = _objectRecognizer[_firedObjectRecognizer].recognizer->getCloseness();
            }
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
        } else {
            _currentMotionSequence = random(0, _motionSequenceCount);
        }
    }
    if (_currentMotionSequence >= 0) {
        _currentMotionSequenceItem = 0;
        _currentMotionSequenceItemStarts = 0;
    } else {
        _playJingleAlarm();
    }
}

void NGMotionUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    _steeringControl->initialize();
    _steeringControl->stop();
    _soundMachine->initialize();
    if (_lightSensor != nullptr) {
        _lightSensor->initialize();
    }
    if (_flashingLightLeft != nullptr) {
        _flashingLightLeft->initialize();
    }
    if (_flashingLightRight != nullptr) {
        _flashingLightRight->initialize();
    }
    if (_brakeLightPin != -1) {
        pinMode(_brakeLightPin, OUTPUT);
    }
    if (_motionMimic != nullptr) {
        _motionMimic->initialize();
    }
    for (int i = 0; i < _objectRecognizerCount; i++) {
        _objectRecognizer[i].recognizer->initialize();
    }
    if (_laserCannon != nullptr) {
        _laserCannon->initialize();
    }
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

void NGMotionUnitControl::registerStartup(int pinStartup, NGCustomJingle *jingle) {
    registerStartup(pinStartup, jingle, DEFSTARTUPLOOPSCOUNT);
}

void NGMotionUnitControl::registerStartup(int pinStartup, NGCustomJingle *jingle, int loops) {
    NGCustomUnitControl::registerStartup(pinStartup);
    _jingleStartup = _soundMachine->registerJingle(jingle);
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

byte NGMotionUnitControl::registerMotionSequence(motionSequenceKind kind) {
    byte res = _motionSequenceCount;
    motionSequence mss;
    mss.kind = kind;
    mss.itemCount = 0;
    _motionSequence[_motionSequenceCount] = mss;
    _motionSequenceCount++;
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
    motionSequenceItem msi;
    msi.speed = speed;
    msi.direction = direction;
    msi.turn = turn;
    msi.duration = duration;
    msi.light = light;
    _motionSequence[motionSequence].items[_motionSequence[motionSequence].itemCount] = msi;
    _motionSequence[motionSequence].itemCount++;
}

void NGMotionUnitControl::registerJingleBackward(NGCustomJingle *jingle) {
    _jingleBackward = _soundMachine->registerJingle(jingle);
}

void NGMotionUnitControl::registerJingleAlarm(NGCustomJingle *jingle) {
    _jingleAlarm = _soundMachine->registerJingle(jingle);
}

void NGMotionUnitControl::registerJingleThinking(NGCustomJingle *jingle) {
    _jingleThinking = _soundMachine->registerJingle(jingle);
}

void NGMotionUnitControl::registerMotionMimic(NGCustomMotionMimic *mimic) {
    _motionMimic = mimic;
}

void NGMotionUnitControl::registerObjectRecognizer(NGCustomObjectRecognizer *recognizer) {
    registerObjectRecognizer(ormpNone, recognizer);
}

void NGMotionUnitControl::registerObjectRecognizer(objectRecognizerMountedPosition mounted, NGCustomObjectRecognizer *recognizer) {
    objectRecognizer objRec;
    objRec.mounted = mounted;
    objRec.recognizer = recognizer;
    _objectRecognizer[_objectRecognizerCount] = objRec;
    _objectRecognizerCount++;
}

void NGMotionUnitControl::registerLaserCannon(NGLaserCannon *lasercannon) {
    _laserCannon = lasercannon;
}

void NGMotionUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    _processingLightSensor();
    _processingFlashingLights();
    _processingObjectRecognizer();
    _processingMotionSequence();
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
    if (_brakeLightPin != -1) {
        if (side == flsBrake) {
            if (on) {
                digitalWrite(_brakeLightPin, HIGH);
            } else {
                digitalWrite(_brakeLightPin, LOW);
            }
        }
    }
}

void NGMotionUnitControl::setWarningLight(bool on) {
    setFlashingLight(flsBoth, on);
}
