//
//  NGMachineControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.05.21.
//

#include "NGMachineControl.h"

NGMachineControl::NGMachineControl() {
    _create(DEFAULTSERIALRATE);
}

NGMachineControl::NGMachineControl(int serialRate) {
    _create(serialRate);
}

void NGMachineControl::_create(int serialRate) {
    _initialized = false;
    _logging = true;
    _serialRate = serialRate;
}

int NGMachineControl::getGripperIndex(char* name) {
    for (int i = 0; i < _grippersCount; i++) {
        if (_gripperData[i].name == name) {
            return i;
        }
    }
    return -1;
}

void NGMachineControl::initialize() {
    char log[100];
    if (_logging) {
        sprintf(log, "Start initialization of NGMachineControl with %d joints and %d grippers...", _jointsCount, _grippersCount);
        Serial.println(log);
    }
    for (int i = 0; i < _grippersCount; i++) {
        gripperData gd = _gripperData[i];
        sprintf(log, "Start initialization of Gripper %s...", gd.name);
        Serial.println(log);
        _grippers[i].initialize(gd.minSpeed, gd.maxSpeed);
        sprintf(log, "...Gripper %s successfully initialized", gd.name);
        Serial.println(log);
    }
    _initialized = true;
    if (_logging) {
        sprintf(log, "...NGMachineControl with %d joints and %d grippers successfully initialized", _jointsCount, _grippersCount);
        Serial.println(log);
    }
}

void NGMachineControl::registerGripper(char* name, int engine, int minSpeed, int maxSpeed) {
    gripperData gd;
    gd.name = name;
    gd.minSpeed = minSpeed;
    gd.maxSpeed = maxSpeed;
    _gripperData[_grippersCount] = gd;
    _grippers[_grippersCount] = NGGripperControl(engine, _serialRate);
    _grippersCount++;
}

void NGMachineControl::gripperGrip(char* name) {
    int index = getGripperIndex(name);
    if (index >= 0) {
        _grippers[index].grip();
    }
}

void NGMachineControl::gripperRelease(char* name) {
    int index = getGripperIndex(name);
    if (index >= 0) {
        _grippers[index].release();
    }
}
