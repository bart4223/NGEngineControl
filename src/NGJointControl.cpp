//
//  NGJointControl.cpp
//  NGJointControl
//
//  Created by Nils Grimmer on 11.05.21.
//

#include "NGJointControl.h"

NGJointControl::NGJointControl(int joint) {
    _create(joint, 9600);
}

NGJointControl::NGJointControl(int joint, int serialRate) {
    _create(joint, serialRate);
}

void NGJointControl::_create(int joint, int serialRate) {
    _joint = joint;
    _initialized = false;
    _logging = true;
    int engine;
    switch (_joint) {
        case JOINT_0:
            engine = ENGINE_0;
            _transducerPin = JOINT_0_TRANSDUCER;
            break;
        case JOINT_1:
            engine = ENGINE_1;
            _transducerPin = JOINT_1_TRANSDUCER;
            break;
        case JOINT_2:
            engine = ENGINE_2;
            _transducerPin = JOINT_2_TRANSDUCER;
            break;
    }
    _engine = NGEngineControl(engine, serialRate);
    _engine.setLogging(_logging);
}

void NGJointControl::initialize(char* name, int minRad, int maxRad, int maxSpeed) {
    char log[100];
    _name = name;
    _engine.initialize();
    if (_logging) {
        sprintf(log, "Start initialization of NGJointControl from joint %s...", _name);
        Serial.println(log);
    }
    _minJointRad = minRad;
    _maxJointRad = maxRad;
    _maxSpeed = maxSpeed;
    _initialized = true;
    if (_logging) {
        sprintf(log, "...NGJointControl from joint %s successfully initialized", _name);
        Serial.println(log);
    }
    read();
}

int NGJointControl::read() {
    char log[100];
    _currentJointRad = analogRead(_transducerPin);
    if (_logging) {
        sprintf(log, "Current rad of joint %s is %d", _name, _currentJointRad);
        Serial.println(log);
    }
    return _currentJointRad;
}

void NGJointControl::move(int targetRad) {
    read();
    _engine.setSpeed(_maxSpeed);
    while (_currentJointRad <= (targetRad - _transducerThreshold) || (targetRad + _transducerThreshold) <= _currentJointRad) {
        if (_currentJointRad < targetRad) {
            setLogging(false);
            _engine.run(edBackward);
            
        } else if (_currentJointRad > targetRad) {
            setLogging(false);
            _engine.run(edForward);
        }
        read();
        delay(_engineMoveDelay);
    }
    _engine.stop();
    setLogging(true);
    read();
}

void NGJointControl::simulate() {
    read();
    if (_currentJointRad >= _maxJointRad - ((_maxJointRad - _minJointRad) / 2)) {
        move(_minJointRad);
    }
    else {
        move(_maxJointRad);
    }
}

char* NGJointControl::getName() {
    return _name;
}

void NGJointControl::setLogging(bool logging) {
    _logging = logging;
    _engine.setLogging(_logging);
}

void NGJointControl::setMinJointRad(int value) {
    _minJointRad = value;
}

int NGJointControl::getMinJointRad() {
    return _minJointRad;
}

void NGJointControl::setMaxJointRad(int value) {
    _maxJointRad = value;
}

int NGJointControl::getMaxJointRad() {
    return _maxJointRad;
}

void NGJointControl::setMaxSpeed(int value) {
    _maxSpeed = value;
}
