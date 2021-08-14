//
//  NGJointControl.cpp
//  NGJointControl
//
//  Created by Nils Grimmer on 11.05.21.
//

#include "NGCommon.h"
#include "NGJointControl.h"

NGJointControl::NGJointControl() {
    
}

NGJointControl::NGJointControl(int joint) {
    _create(joint, DEFAULTENGINE, DEFAULTSERIALRATE);
}

NGJointControl::NGJointControl(int joint, int engine) {
    _create(joint, engine, DEFAULTSERIALRATE);
}

NGJointControl::NGJointControl(int joint, int engine, int serialRate) {
    _create(joint, engine, serialRate);
}

void NGJointControl::_create(int joint, int engine, int serialRate) {
    _joint = joint;
    _initialized = false;
    _logging = true;
    switch (_joint) {
        case JOINT_0:
            if (engine == DEFAULTENGINE) {
                engine = ENGINE_0;
            }
            _transducerPin = JOINT_0_TRANSDUCER;
            break;
        case JOINT_1:
            if (engine == DEFAULTENGINE) {
                engine = ENGINE_1;
            }
            _transducerPin = JOINT_1_TRANSDUCER;
            break;
        case JOINT_2:
            if (engine == DEFAULTENGINE) {
                engine = ENGINE_2;
            }
            _transducerPin = JOINT_2_TRANSDUCER;
            break;
    }
    _engine = NGEngineControl(engine, serialRate);
    _engine.setLogging(_logging);
}

void NGJointControl::initialize(int minRad, int maxRad) {
    initialize(minRad, maxRad, MAXSPEED);
}

void NGJointControl::initialize(int minRad, int maxRad, int maxSpeed) {
    initialize(NONAME, minRad, maxRad, maxSpeed);
}

void NGJointControl::initialize(char* name, int minRad, int maxRad) {
    initialize(name, minRad, maxRad, MAXSPEED);
}

void NGJointControl::initialize(char* name, int minRad, int maxRad, int maxSpeed) {
    char log[100];
    _name = name;
    _engine.initialize();
    _minJointRad = minRad;
    _maxJointRad = maxRad;
    _maxSpeed = maxSpeed;
    _initialized = true;
    if (_logging) {
        if (_name != "" ) {
            sprintf(log, "Joint %s with engine %d initialized", _name, _engine);
        } else {
            sprintf(log, "Joint %d with engine %d initialized", _joint, _engine);
        }
        Serial.println(log);
    }
    read();
}

int NGJointControl::read() {
    char log[100];
    _currentJointRad = analogRead(_transducerPin);
    if (_logging) {
        if (_name != "" ) {
            sprintf(log, "Rad of joint %s is %d", _name, _currentJointRad);
        }
        else {
            sprintf(log, "Rad of joint %d is %d", _joint, _currentJointRad);
        }
        Serial.println(log);
    }
    return _currentJointRad;
}

bool NGJointControl::move(int targetRad) {
    setLogging(false);
    read();
    _engine.setSpeed(_maxSpeed);
    int ticks = 0;
    while ((_currentJointRad <= (targetRad - _transducerThreshold) || (targetRad + _transducerThreshold) <= _currentJointRad) && ticks <= _maxMoveTicks) {
        if (_currentJointRad < targetRad) {
            setLogging(false);
            _engine.run(edBackward);
            
        } else if (_currentJointRad > targetRad) {
            setLogging(false);
            _engine.run(edForward);
        }
        read();
        delay(_engineMoveDelay);
        if (_maxMoveTicks != 0) {
            ticks++;
        }
    }
    _engine.stop();
    delay(_engineMoveDelay);
    read();
    bool res = (targetRad - _transducerThreshold) <= _currentJointRad && _currentJointRad <= (targetRad + _transducerThreshold);
    setLogging(res);
    read();
    setLogging(true);
    return res;
}

void NGJointControl::simulate() {
    read();
    bool reached;
    if (_currentJointRad >= _maxJointRad - ((_maxJointRad - _minJointRad) / 2)) {
        do {
            reached = move(_minJointRad);
        } while (reached);
    }
    else {
        do {
            reached = move(_maxJointRad);
        } while (reached);
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

void NGJointControl::setMaxMoveTicks(int value) {
    _maxMoveTicks = value;
}

int NGJointControl::getMaxSpeed() {
    return _maxSpeed;
}
