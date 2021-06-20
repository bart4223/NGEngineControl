//
//  NGUnitControl.cpp
//  NGUnitControl
//
//  Created by Nils Grimmer on 29.05.21.
//

#include "Wire.h"
#include "NGCommon.h"
#include "NGUnitControl.h"

void _unitWireReceiveEvent(int byteCount) {
    int i = 0;
    _unit->receiveDataStart();
    while(Wire.available())
    {
        byte b = Wire.read();
        _unit->receivedData(i, b);
        //Serial.println(b);
        i++;
    }
    _unit->receiveDataFinish(byteCount);
}

NGUnitControl::NGUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE);
}

NGUnitControl::NGUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE);
}

NGUnitControl::NGUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE);
}

NGUnitControl::NGUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate);
}

void NGUnitControl::_create(char* name, byte address, int serialRate) {
    NGCustomUnitControl::_create(name, address, serialRate);
    Wire.begin(_address);
    Wire.onReceive(_unitWireReceiveEvent);
}

int NGUnitControl::getEngineIndex(char* name) {
    for (int i = 0; i < _enginesCount; i++) {
        if (_engineData[i].name == name) {
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

int NGUnitControl::getGripperIndex(char* name) {
    for (int i = 0; i < _grippersCount; i++) {
        if (_gripperData[i].name == name) {
            return i;
        }
    }
    return -1;
}

void NGUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    for (int i = 0; i < _enginesCount; i++) {
        _engines[i]->initialize(_engineData[i].initSpeed);
    }
    for (int i = 0; i < _jointsCount; i++) {
        _joints[i]->initialize(_jointData[i].name, _jointData[i].minRad, _jointData[i].maxRad);
    }
    for (int i = 0; i < _grippersCount; i++) {
        _grippers[i]->initialize(_gripperData[i].minSpeed, _gripperData[i].maxSpeed);
    }
    _initialized = true;
    if (_logging) {
        char log[100];
        sprintf(log, "...Unit \"%s\" with %d pure engines, %d joints and %d grippers initialized", _name, _enginesCount, _jointsCount, _grippersCount);
        writeInfo(log);
    }
}

void NGUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    for (int i = 0; i < _jointsCount; i++) {
        if (_jointData[i].targetRad != 0) {
            if (_joints[i]->move(_jointData[i].targetRad)) {
                _jointData[i].targetRad = 0;
            }
        }
    }
}

void NGUnitControl::registerEngine(char* name, NGEngineControl *engine) {
    registerEngine(name, engine, MAXSPEED);
}

void NGUnitControl::registerEngine(char* name, NGEngineControl *engine, int initSpeed) {
    engineData ed;
    ed.name = name;
    ed.initSpeed = initSpeed;
    _engineData[_enginesCount] = ed;
    _engines[_enginesCount] = engine;
    _enginesCount++;
    if (_logging) {
        char log[100];
        sprintf(log, "Engine \"%s.%s\" registered", _name, name);
        writeInfo(log);
    }
}

void NGUnitControl::engineRun(char* name, engineDirection direction) {
    int index = getEngineIndex(name);
    if (index >= 0) {
        _engines[index]->run(direction);
    }
}

void NGUnitControl::engineStop(char* name) {
    int index = getEngineIndex(name);
    if (index >= 0) {
        _engines[index]->stop();
    }
}

void NGUnitControl::engineSetSpeed(char* name, int speed) {
    int index = getEngineIndex(name);
    if (index >= 0) {
        _engines[index]->setSpeed(speed);
    }
}

void NGUnitControl::registerJoint(char* name, NGJointControl *joint, int minRad, int maxRad) {
    registerJoint(name, joint, minRad, maxRad, DEFAULTMAXMOVETICKS, DEFAULTENGINE);
}

void NGUnitControl::registerJoint(char* name, NGJointControl *joint, int minRad, int maxRad, int maxMoveTicks) {
    registerJoint(name, joint, minRad, maxRad, maxMoveTicks, DEFAULTENGINE);
}

void NGUnitControl::registerJoint(char* name, NGJointControl *joint, int minRad, int maxRad, int maxMoveTicks, int engine) {
    jointData jd;
    jd.name = name;
    jd.minRad = minRad;
    jd.maxRad = maxRad;
    jd.targetRad = 0;
    _jointData[_jointsCount] = jd;
    _joints[_jointsCount] = joint;
    if (maxMoveTicks != DEFAULTMAXMOVETICKS) {
        joint->setMaxMoveTicks(maxMoveTicks);
    }
    _jointsCount++;
    if (_logging) {
        char log[100];
        sprintf(log, "Joint \"%s.%s\" registered", _name, name);
        writeInfo(log);
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
    bool res = index >= 0;
    if (res) {
        res = (targetRad >= _joints[index]->getMinJointRad() && targetRad <= _joints[index]->getMaxJointRad());
        if (res) {
            res = _joints[index]->move(targetRad);
            if (!res) {
                _jointData[index].targetRad = targetRad;
            }
        } else {
            if (_logging) {
                char log[100];
                sprintf(log, "Radiant of joint %s is invalid", name);
                writeInfo(log);
            }
        }
    }
    return res;
}

bool NGUnitControl::jointIsMoving(char* name) {
    int index = getJointIndex(name);
    bool res = index >= 0;
    if (res) {
        res = _jointData[index].targetRad != 0;
    }
    return res;
}

void NGUnitControl::jointSimulate(char* name) {
    int index = getJointIndex(name);
    if (index >= 0) {
        _joints[index]->simulate();
    }
}

void NGUnitControl::registerGripper(char* name, NGGripperControl *gripper, int minSpeed, int maxSpeed) {
    gripperData gd;
    gd.name = name;
    gd.minSpeed = minSpeed;
    gd.maxSpeed = maxSpeed;
    _gripperData[_grippersCount] = gd;
    _grippers[_grippersCount] = gripper;
    _grippersCount++;
    if (_logging) {
        char log[100];
        sprintf(log, "Gripper \"%s.%s\" registered", _name, name);
        writeInfo(log);
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
