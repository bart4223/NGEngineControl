//
//  NGCarSteeringControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 10.08.22.
//

#include "NGCommon.h"
#include "NGCarSteeringControl.h"

NGCarSteeringControl::NGCarSteeringControl() {
    _create(ENGINE_0, DEFAULTSERIALRATE, DEFSERVOPIN, DEFSERVOZEROPOSITION, DEFSERVOMINPOSITION, DEFSERVOMAXPOSITION, DEFSERVOSTEPWIDTH);
}

NGCarSteeringControl::NGCarSteeringControl(byte pinSteering, byte steeringZeroPos, byte steeringMin, byte steeringMax, byte steeringStepWith) {
    _create(ENGINE_0, DEFAULTSERIALRATE, pinSteering, steeringZeroPos, steeringMin, steeringMax, steeringStepWith);
}

NGCarSteeringControl::NGCarSteeringControl(int engine, byte pinSteering, byte steeringZeroPos, byte steeringMin, byte steeringMax, byte steeringStepWith) {
    _create(engine, DEFAULTSERIALRATE, pinSteering, steeringZeroPos, steeringMin, steeringMax, steeringStepWith);
}

void NGCarSteeringControl::_create(int engine, int serialRate, byte pinSteering, byte steeringZeroPos, byte steeringMin, byte steeringMax, byte steeringStepWith) {
    _engine = new NGEngineControl(engine, serialRate);
    _steering = new NGServoControl(pinSteering, steeringZeroPos, steeringMin, steeringMax, steeringStepWith);
    _engine->setLogging(_logging);
    _steering->setLogging(_logging);
}

void NGCarSteeringControl::initialize() {
    char log[100];
    _engine->initialize();
    _steering->initialize();
    _initialized = true;
    if (_logging) {
        sprintf(log, "Car steering with engine %d initialized", _engine->getID());
        Serial.println(log);
    }
}

void NGCarSteeringControl::stop() {
    _engine->stop();
    if (_logging) {
        Serial.println("Engine stopped");
    }
}

void NGCarSteeringControl::run(engineDirection direction, byte speed) {
    char log[100];
    if (speed > NULLSPEED) {
        _speed = speed;
    }
    _engine->setSpeed(_speed);
    _engine->run(direction);
    if (_logging) {
        if (direction == edForward) {
            sprintf(log, "Engine runs with speed %d forward", _speed);
        } else {
            sprintf(log, "Engine runs with speed %d backward", _speed);
        }
        Serial.println(log);
    }
}

void NGCarSteeringControl::turnForward(turnDirection turn, byte speed) {
    switch(turn) {
        case tdLeft:
        case tdLeftSoft:
            if (!_steering->isMinPosition()) {
                _steering->stepDown();
            }
            break;
        case tdRight:
        case tdRightSoft:
            if (!_steering->isMaxPosition()) {
                _steering->stepUp();
            }
            break;
    }
    _engine->setSpeed(speed);
    _engine->run(edForward);
}

void NGCarSteeringControl::turnBackward(turnDirection turn, byte speed) {
    switch(turn) {
        case tdLeft:
        case tdLeftSoft:
            if (!_steering->isMinPosition()) {
                _steering->stepDown();
            }
            break;
        case tdRight:
        case tdRightSoft:
            if (!_steering->isMaxPosition()) {
                _steering->stepUp();
            }
            break;
    }
    _engine->setSpeed(speed);
    _engine->run(edBackward);
}

void NGCarSteeringControl::runFullSpeedForward() {
    run(edForward, MAXSPEED);
}

void NGCarSteeringControl::runFullSpeedBackward() {
    run(edBackward, MAXSPEED);
}

void NGCarSteeringControl::run(engineDirection direction) {
    run(direction, NULLSPEED);
}

void NGCarSteeringControl::turnForward(turnDirection turn) {
    turnForward(turn, NULLSPEED);
}

void NGCarSteeringControl::turnBackward(turnDirection turn) {
    turnBackward(turn, NULLSPEED);
}
