//
//  NGUnitControl.cpp
//  NGUnitControl
//
//  Created by Nils Grimmer on 29.05.21.
//

#include "NGUnitControl.h"

NGUnitControl::NGUnitControl() {
    _create(NONAME, DEFAULTSERIALRATE);
}

NGUnitControl::NGUnitControl(char* name) {
    _create(name, DEFAULTSERIALRATE);
}

NGUnitControl::NGUnitControl(char* name, int serialRate) {
    _create(name, serialRate);
}

void NGUnitControl::_create(char* name, int serialRate) {
    _name = name;
    _serialRate = serialRate;
    _initialized = false;
    _logging = true;
}

int NGUnitControl::getGripperIndex(char* name) {
    for (int i = 0; i < _grippersCount; i++) {
        if (_gripperData[i].name == name) {
            return i;
        }
    }
    return -1;
}

int NGUnitControl::getJointIndex(char* name) {
    for (int i = 0; i < _jointsCount; i++) {
        if (_jointData[i].name == name) {
            return i;
        }
    }
    return -1;
}

void NGUnitControl::initialize() {
    char log[100];
    _ensureGlobalSerial(_serialRate);
    if (_logging) {
        sprintf(log, "Start initialization of NGUnitControl \"%s\" with %d joints and %d grippers...", _name, _jointsCount, _grippersCount);
        Serial.println(log);
    }
    for (int i = 0; i < _grippersCount; i++) {
        gripperData gd = _gripperData[i];
        sprintf(log, "Start initialization of gripper \"%s.%s\"...", _name, gd.name);
        Serial.println(log);
        _grippers[i]->initialize(gd.minSpeed, gd.maxSpeed);
        sprintf(log, "...gripper \"%s.%s\" of NGUnitControl successfully initialized", _name, gd.name);
        Serial.println(log);
    }
    for (int i = 0; i < _jointsCount; i++) {
        jointData jd = _jointData[i];
        sprintf(log, "Start initialization of joint \"%s.%s\"...", _name, jd.name);
        Serial.println(log);
        _joints[i]->initialize(jd.name, jd.minRad, jd.maxRad);
        sprintf(log, "...joint \"%s.%s\" of NGUnitControl successfully initialized", _name, jd.name);
        Serial.println(log);
    }
    _initialized = true;
    if (_logging) {
        sprintf(log, "...NGUnitControl \"%s\" with %d joints and %d grippers successfully initialized", _name, _jointsCount, _grippersCount);
        Serial.println(log);
    }
}

void NGUnitControl::registerJoint(char* name, int joint, int minRad, int maxRad) {
    registerJoint(name, joint, minRad, maxRad, DEFAULTENGINE);
}

void NGUnitControl::registerJoint(char* name, int joint, int minRad, int maxRad, int engine) {
    char log[100];
    _ensureGlobalSerial(_serialRate);
    jointData jd;
    jd.name = name;
    jd.minRad = minRad;
    jd.maxRad = maxRad;
    _jointData[_jointsCount] = jd;
    _joints[_jointsCount] = new NGJointControl(joint, engine, _serialRate);
    _jointsCount++;
    if (_logging) {
        sprintf(log, "Joint \"%s.%s\" with joint %d successfully registered", _name, name, joint);
        Serial.println(log);
    }
}

void NGUnitControl::jointRead(char* name) {
    int index = getJointIndex(name);
    if (index >= 0) {
        _joints[index]->read();
    }
}

void NGUnitControl::registerGripper(char* name, int engine, int minSpeed, int maxSpeed) {
    char log[100];
    _ensureGlobalSerial(_serialRate);
    gripperData gd;
    gd.name = name;
    gd.minSpeed = minSpeed;
    gd.maxSpeed = maxSpeed;
    _gripperData[_grippersCount] = gd;
    _grippers[_grippersCount] = new NGGripperControl(engine, _serialRate);
    _grippersCount++;
    if (_logging) {
        sprintf(log, "Gripper \"%s.%s\" with engine %d successfully registered", _name, name, engine);
        Serial.println(log);
    }
}

void NGUnitControl::gripperGrip(char* name) {
    int index = getGripperIndex(name);
    if (index >= 0) {
        _grippers[index]->grip();
    }
}

void NGUnitControl::gripperRelease(char* name) {
    int index = getGripperIndex(name);
    if (index >= 0) {
        _grippers[index]->release();
    }
}
