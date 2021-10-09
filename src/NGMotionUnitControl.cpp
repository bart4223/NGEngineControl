//
//  NGMotionUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 28.09.21.
//

#include "NGCommon.h"
#include "NGMemoryObserver.h"
#include "NGMotionUnitControl.h"

NGMotionUnitControl::NGMotionUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE, ENGINE_0, ENGINE_1);
}

NGMotionUnitControl::NGMotionUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE, ENGINE_0, ENGINE_1);
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE, ENGINE_0, ENGINE_1);
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate, ENGINE_0, ENGINE_1);
}

NGMotionUnitControl::NGMotionUnitControl(char* name, byte address, int serialRate, int engineLeft, int engineRight) {
    _create(name, address, serialRate, engineLeft, engineRight);
}

void NGMotionUnitControl::_create(char* name, byte address, int serialRate, int engineLeft, int engineRight) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    _steeringControl = new NGSteeringControl(engineLeft, engineRight);
    _soundMachine = new NGSoundMachine();
}

void NGMotionUnitControl::_processingReceivedData() {
    
}

void NGMotionUnitControl::_playJingleStartup() {
    if (_jingleStartup != -1) {
        for (int i = 0; i < _jingleStartupLoops; i++) {
            _soundMachine->play(_jingleStartup);
        }
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

void NGMotionUnitControl::_processingMotionSequence() {
    if (_currentMotionSequence == -1) {
        if (_motionSequenceCount > 0) {
            _currentMotionSequence = random(0, _motionSequenceCount);
            _currentMotionSequenceItem = 0;
            _currentMotionSequenceItemStarts = 0;
        }
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
            } else {
                _steeringControl->run(item.direction, item.speed);
            }
            break;
        case tdLeft: tdRight:
            if (item.direction == edForward) {
                _steeringControl->turnForward(item.turn);
            }
            break;
    }
    if (item.light == flsNone) {
        setFlashingLight(flsBoth, false);
    } else {
        setFlashingLight(item.light, item.light != flsNone);
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
    addMotionSequenceItem(motionSequence, 0, edNone, tdNone, duration);
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

void NGMotionUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    _processingLightSensor();
    _processingFlashingLights();
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
}

void NGMotionUnitControl::setWarningLight(bool on) {
    setFlashingLight(flsBoth, on);
}
