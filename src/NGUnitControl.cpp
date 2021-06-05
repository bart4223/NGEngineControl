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

void NGUnitControl::initialize() {
    char log[100];
    _ensureGlobalSerial(_serialRate);
    if (_logging) {
        sprintf(log, "Start initialization of NGUnitControl \"%s\" with %d joints and %d grippers...", _name, _jointsCount, _grippersCount);
        Serial.println(log);
    }
    for (int i = 0; i < _grippersCount; i++) {
        gripperData gd = _gripperData[i];
        sprintf(log, "Start initialization of Gripper \"%s.%s\"...", _name, gd.name);
        Serial.println(log);
        _grippers[i]->initialize(gd.minSpeed, gd.maxSpeed);
        sprintf(log, "...Gripper \"%s.%s\" successfully initialized", _name, gd.name);
        Serial.println(log);
    }
    _initialized = true;
    if (_logging) {
        sprintf(log, "...NGUnitControl \"%s\" with %d joints and %d grippers successfully initialized", _name, _jointsCount, _grippersCount);
        Serial.println(log);
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
        sprintf(log, "Gripper \"%s.%s\" successfully registered", _name, name);
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
