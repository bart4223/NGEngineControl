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
    for (int i = 0; i < _jointsCount; i++) {
        _joints[i]->initialize(_jointData[i].name, _jointData[i].minRad, _jointData[i].maxRad);
    }
    for (int i = 0; i < _grippersCount; i++) {
        _grippers[i]->initialize(_gripperData[i].minSpeed, _gripperData[i].maxSpeed);
    }
    _initialized = true;
    if (_logging) {
        sprintf(log, "...Unit \"%s\" with %d joints and %d grippers initialized", _name, _jointsCount, _grippersCount);
        Serial.println(log);
    }
}

void NGUnitControl::registerJoint(char* name, NGJointControl *joint, int minRad, int maxRad) {
    registerJoint(name, joint, minRad, maxRad, DEFAULTMAXMOVETICKS, DEFAULTENGINE);
}

void NGUnitControl::registerJoint(char* name, NGJointControl *joint, int minRad, int maxRad, int maxMoveTicks) {
    registerJoint(name, joint, minRad, maxRad, maxMoveTicks, DEFAULTENGINE);
}

void NGUnitControl::registerJoint(char* name, NGJointControl *joint, int minRad, int maxRad, int maxMoveTicks, int engine) {
    char log[100];
    _ensureGlobalSerial(_serialRate);
    jointData jd;
    jd.name = name;
    jd.minRad = minRad;
    jd.maxRad = maxRad;
    _jointData[_jointsCount] = jd;
    _joints[_jointsCount] = joint;
    if (maxMoveTicks != DEFAULTMAXMOVETICKS) {
        joint->setMaxMoveTicks(maxMoveTicks);
    }
    _jointsCount++;
    if (_logging) {
        sprintf(log, "Joint \"%s.%s\" registered", _name, name);
        Serial.println(log);
    }
}

void NGUnitControl::jointRead(char* name) {
    int index = getJointIndex(name);
    if (index >= 0) {
        _joints[index]->read();
    }
}

bool NGUnitControl::jointMove(char* name, int targetRad) {
    int index = getJointIndex(name);
    if (index >= 0) {
        return _joints[index]->move(targetRad);
    }
}

void NGUnitControl::jointSimulate(char* name) {
    int index = getJointIndex(name);
    if (index >= 0) {
        _joints[index]->simulate();
    }
}

void NGUnitControl::registerGripper(char* name, NGGripperControl *gripper, int minSpeed, int maxSpeed) {
    char log[100];
    _ensureGlobalSerial(_serialRate);
    gripperData gd;
    gd.name = name;
    gd.minSpeed = minSpeed;
    gd.maxSpeed = maxSpeed;
    _gripperData[_grippersCount] = gd;
    _grippers[_grippersCount] = gripper;
    _grippersCount++;
    if (_logging) {
        sprintf(log, "Gripper \"%s.%s\" registered", _name, name);
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
