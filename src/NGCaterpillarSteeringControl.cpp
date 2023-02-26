//
//  NGCaterpillarSteeringControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 26.02.23.
//

#include "NGCommon.h"
#include "NGCaterpillarSteeringControl.h"

NGCaterpillarSteeringControl::NGCaterpillarSteeringControl() {
    _create(ENGINE_0, ENGINE_1, ENGINE_2, DEFAULTSERIALRATE);
}

NGCaterpillarSteeringControl::NGCarSteeringControl(int engineMain, int engineRight, int engineLeft) {
    _create(engineMain, engineRight, engineLeft, DEFAULTSERIALRATE);
}

void NGCaterpillarSteeringControl::_create(int engineMain, int engineRight, int engineLeft, int serialRate) {
    _engineMain = new NGEngineControl(engineMain, serialRate);
    _engineRight = new NGEngineControl(engineRight, serialRate);
    _engineLeft = new NGEngineControl(engineLeft, serialRate);
    _engineMain->setLogging(_logging);
    _engineRight->setLogging(_logging);
    _engineLeft->setLogging(_logging);
}

void NGCaterpillarSteeringControl::initialize() {
    char log[100];
    _engineMain->setLogging(_logging);
    _engineMain->initialize();
    _engineRight->setLogging(_logging);
    _engineRight->initialize();
    _engineLeft->setLogging(_logging);
    _engineLeft->initialize();
    _initialized = true;
    if (_logging) {
        sprintf(log, "Caterpillar steering with main engine %d right engine %d left engine %d initialized", _engineMain->getID(),  _engineRight->getID(),  _engineLeft->getID());
        Serial.println(log);
    }
}

void NGCaterpillarSteeringControl::stop() {
    _engineMain->stop();
    _engineRight->stop();
    _engineLeft->stop();
    if (_logging) {
        Serial.println("Engines stopped");
    }
}

void NGCaterpillarSteeringControl::run(engineDirection direction, byte speed) {
    char log[100];
    if (speed > NULLSPEED) {
        _speed = speed;
    }
    _engineMain->setSpeed(_speed * 0.5);
    _engineMain->run(direction);
    _engineRight->setSpeed(_speed);
    _engineRight->run(direction);
    _engineLeft->setSpeed(_speed);
    _engineLeft->run(direction);
    if (_logging) {
        if (direction == edForward) {
            sprintf(log, "Engines runs with speed %d forward", _speed);
        } else {
            sprintf(log, "Engines runs with speed %d backward", _speed);
        }
        Serial.println(log);
    }
}

void NGCaterpillarSteeringControl::turnForward(turnDirection turn, byte speed) {
    switch(turn) {
        case tdLeft:
        case tdLeftSoft:
            _engineRight->setSpeed(_speed);
            _engineRight->run(edForward);
            _engineLeft->setSpeed(_speed);
            _engineLeft->run(edBackward);
            break;
        case tdRight:
        case tdRightSoft:
            _engineRight->setSpeed(_speed);
            _engineRight->run(edBackward);
            _engineLeft->setSpeed(_speed);
            _engineLeft->run(edForward);
            break;
    }
    if (speed == 0) {
        _engineMain->setSpeed(_speed);
        _engineMain->run(edForward);
    }
}

void NGCaterpillarSteeringControl::turnBackward(turnDirection turn, byte speed) {
    switch(turn) {
        case tdLeft:
        case tdLeftSoft:
            _engineRight->setSpeed(_speed);
            _engineRight->run(edBackward);
            _engineLeft->setSpeed(_speed);
            _engineLeft->run(edForward);
            break;
        case tdRight:
        case tdRightSoft:
            _engineRight->setSpeed(_speed);
            _engineRight->run(edForward);
            _engineLeft->setSpeed(_speed);
            _engineLeft->run(edBackward);
            break;
    }
    if (speed == 0) {
        _engineMain->setSpeed(_speed);
        _engineMain->run(edBackward);
    }
}

void NGCaterpillarSteeringControl::runFullSpeedForward() {
    run(edForward, MAXSPEED);
}

void NGCaterpillarSteeringControl::runFullSpeedBackward() {
    run(edBackward, MAXSPEED);
}

void NGCaterpillarSteeringControl::run(engineDirection direction) {
    run(direction, NULLSPEED);
}

void NGCaterpillarSteeringControl::turnForward(turnDirection turn) {
    turnForward(turn, NULLSPEED);
}

void NGCaterpillarSteeringControl::turnBackward(turnDirection turn) {
    turnBackward(turn, NULLSPEED);
}

bool NGCaterpillarSteeringControl::isRunning() {
    return _engineMain->isRunning();
}
