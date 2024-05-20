//
//  NGCaterpillarSteeringControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 26.02.23.
//

#include "NGCommon.h"
#include "NGCaterpillarSteeringControl.h"

NGCaterpillarSteeringControl::NGCaterpillarSteeringControl() {
    _create(ENGINE_0, ENGINE_1, DEFAULTSERIALRATE);
}

NGCaterpillarSteeringControl::NGCarSteeringControl(int engineRear, int engineBow) {
    _create(engineRear, engineBow, DEFAULTSERIALRATE);
}

void NGCaterpillarSteeringControl::_create(int engineRear, int engineBow, int serialRate) {
    _engineRear = new NGEngineControl(engineRear, serialRate);
    _engineBow = new NGEngineControl(engineBow, serialRate);
    _engineRear->setLogging(_logging);
    _engineBow->setLogging(_logging);
}

void NGCaterpillarSteeringControl::initialize() {
    char log[100];
    _engineRear->setLogging(_logging);
    _engineRear->initialize();
    _engineBow->setLogging(_logging);
    _engineBow->initialize();
    _initialized = true;
    if (_logging) {
        sprintf(log, "Caterpillar steering with rear engine %d and bow engine %d initialized", _engineRear->getID(),  _engineBow->getID());
        Serial.println(log);
    }
}

void NGCaterpillarSteeringControl::stop() {
    _engineRear->stop();
    _engineBow->stop();
    if (_logging) {
        Serial.println("Engines stopped");
    }
}

void NGCaterpillarSteeringControl::run(engineDirection direction, byte speed) {
    char log[100];
    if (speed > NULLSPEED) {
        _speed = speed;
    }
    _engineRear->setSpeed(_speed);
    _engineRear->run(direction);
    _engineBow->setSpeed(_speed);
    _engineBow->run(direction);
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
            _engineRear->setSpeed(_speed);
            _engineRear->run(edBackward);
            _engineBow->setSpeed(_speed);
            _engineBow->run(edForward);
            break;
        case tdRight:
        case tdRightSoft:
            _engineRear->setSpeed(_speed);
            _engineRear->run(edForward);
            _engineBow->setSpeed(_speed);
            _engineBow->run(edBackward);
            break;
    }
}

void NGCaterpillarSteeringControl::turnBackward(turnDirection turn, byte speed) {
    switch(turn) {
        case tdLeft:
        case tdLeftSoft:
            _engineRear->setSpeed(_speed);
            _engineRear->run(edBackward);
            _engineBow->setSpeed(_speed);
            _engineBow->run(edForward);
            break;
        case tdRight:
        case tdRightSoft:
            _engineRear->setSpeed(_speed);
            _engineRear->run(edBackward);
            _engineBow->setSpeed(_speed);
            _engineBow->run(edForward);
            break;
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
    return _engineRear->isRunning();
}
