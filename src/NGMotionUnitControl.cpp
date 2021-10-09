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
        sprintf(log, "...Unit \"%s\" with steering initialized", _name );
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

void NGMotionUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    _processingLightSensor();
    _processingFlashingLights();
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
    switch(side) {
        case flsLeft:
            if (_flashingLightLeft != nullptr) {
                _flashingLightLeft->setOn(on);
            }
            break;
        case flsRight:
            if (_flashingLightRight != nullptr) {
                _flashingLightRight->setOn(on);
            }
            break;
    }
}

void NGMotionUnitControl::setWarningLight(bool on) {
    setFlashingLight(flsLeft, on);
    setFlashingLight(flsRight, on);
}
