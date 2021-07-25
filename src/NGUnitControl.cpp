//
//  NGUnitControl.cpp
//  NGUnitControl
//
//  Created by Nils Grimmer on 29.05.21.
//

#include "Wire.h"
#include "NGCommon.h"
#include <NGMemoryObserver.h>
#include "NGUnitControl.h"

void _unitWireReceiveEvent(int byteCount) {
    int i = 0;
    globalUnitReceiveDataStart();
    while(Wire.available())
    {
        globalUnitReceivedData(i, Wire.read());
        i++;
    }
    globalUnitReceiveDataFinish(byteCount);
}

void _unitWireRequestEvent() {
    byte b[REQUESTEDDATALENGTH];
    globalUnitRequestData(b);
    Wire.write(b, REQUESTEDDATALENGTH);
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
    _version = VERSION;
    Wire.begin(_address);
    Wire.onReceive(_unitWireReceiveEvent);
    Wire.onRequest(_unitWireRequestEvent);
}

void NGUnitControl::_nop() {
    
}

void NGUnitControl::_processingReceivedData() {
    if (_receivedDataCount <= 3) {
        clearInfo();
        char* cmd = (char*)malloc(_receivedDataCount + 1);
        memcpy(cmd, _receivedData, _receivedDataCount);
        cmd[_receivedDataCount] = '\0';
        writeInfo(cmd);
        free(cmd);
    }
    else {
        switch (_receivedData[CMDSubject]) {
            case CMDSNone:
                _processingReceivedDataNone();
                break;
            case CMDSEngine:
                _processingReceivedDataEngine();
                break;
            case CMDSJoint:
                _processingReceivedDataJoint();
                break;
            case CMDSGripper:
                _processingReceivedDataGripper();
                break;
        }
    }
}

void NGUnitControl::_processingReceivedDataNone() {
    switch (_receivedData[CMDOperation]) {
        case CMDONop:
            _nop();
            break;
    }
}

void NGUnitControl::_processingReceivedDataEngine() {
    char* n = NULL;
    int size = _getNameSizeFromReceivedData();
    if (size > 0) {
        n = (char*)malloc(size);
        memcpy(n, _receivedData + CMDOffset, size);
        n[size - 1] = '\0';
    }
    switch (_receivedData[CMDOperation]) {
        case CMDONop:
            _nop();
            break;
        case CMDOEngineRunForward:
            clearInfo();
            writeInfo((char*)"forward");
            engineRun(n, edForward);
            break;
        case CMDOEngineRunBackward:
            clearInfo();
            writeInfo((char*)"backward");
            engineRun(n, edBackward);
            break;
        case CMDOEngineStop:
            clearInfo();
            writeInfo((char*)"stop");
            engineStop(n);
            break;
        case CMDOEngineSetSpeed:
            clearInfo();
            int speed = _receivedData[CMDOffset + size];
            writeInfo((char*)"speed");
            engineSetSpeed(n, speed);
            break;
    }
    if (n != NULL) {
        free(n);
    }
}

void NGUnitControl::_processingReceivedDataJoint() {
    char* n = NULL;
    int size = _getNameSizeFromReceivedData();
    if (size > 0) {
        n = (char*)malloc(size);
        memcpy(n, _receivedData + CMDOffset, size);
        n[size - 1] = '\0';
    }
    int currentrad;
    switch (_receivedData[CMDOperation]) {
        case CMDONop:
            _nop();
            break;
        case CMDOJointMove:
            clearInfo();
            int targetrad;
            targetrad = (_receivedData[CMDOffset + size] << 8) | (_receivedData[CMDOffset + size + 1]);
            writeInfo((char*)"move");
            jointMove(n, targetrad);
            currentrad = jointRead(n);
            _requestedData[0] = (currentrad >> 8);
            _requestedData[1] = currentrad;
            break;
        case CMDOJointSimulate:
            clearInfo();
            writeInfo((char*)"simulate");
            jointSimulate(n);
            break;
        case CMDOJointMoveStepToMax:
            clearInfo();
            writeInfo((char*)"step+");
            jointMoveStepToMax(n);
            currentrad = jointRead(n);
            _requestedData[0] = (currentrad >> 8);
            _requestedData[1] = currentrad;
            break;
        case CMDOJointMoveStepToMin:
            clearInfo();
            writeInfo((char*)"step-");
            jointMoveStepToMin(n);
            currentrad = jointRead(n);
            _requestedData[0] = (currentrad >> 8);
            _requestedData[1] = currentrad;
            break;
        case CMDOJointRead:
            clearInfo();
            writeInfo((char*)"read");
            currentrad = jointRead(n);
            _requestedData[0] = (currentrad >> 8);
            _requestedData[1] = currentrad;
            int rad = jointGetMinRad(n);
            _requestedData[2] = (rad >> 8);
            _requestedData[3] = rad;
            rad = jointGetMaxRad(n);
            _requestedData[4] = (rad >> 8);
            _requestedData[5] = rad;
            break;
    }
}

void NGUnitControl::_processingReceivedDataGripper() {
    char* n = NULL;
    int size = _getNameSizeFromReceivedData();
    if (size > 0) {
        n = (char*)malloc(size);
        memcpy(n, _receivedData + CMDOffset, size);
        n[size - 1] = '\0';
    }
    switch (_receivedData[CMDOperation]) {
        case CMDONop:
            _nop();
            break;
        case CMDOGripperGrip:
            clearInfo();
            writeInfo((char*)"grip");
            gripperGrip(n);
            break;
        case CMDOGripperRelease:
            clearInfo();
            writeInfo((char*)"release");
            gripperRelease(n);
            break;
    }
    if (n != NULL) {
        free(n);
    }
}

int NGUnitControl::_getNameSizeFromReceivedData() {
    int res = 1;
    for (int i = CMDOffset; i < _receivedDataCount; i++) {
        if (_receivedData[i] == CMDNameSeparator) {
            return res;
        }
        res++;
    }
    return -1;
}

int NGUnitControl::_getEngineIndex(char* name) {
    for (int i = 0; i < _enginesCount; i++) {
        int ok = 0;
        for (int j = 0; j < strlen(_engineData[i].name); j++) {
            if (_engineData[i].name[j] == name[j]) {
                ok++;
            }
        }
        if (ok == strlen(_engineData[i].name)) {
            return i;
        }
    }
    return -1;
}

int NGUnitControl::_getJointIndex(char* name) {
    for (int i = 0; i < _jointsCount; i++) {
        int ok = 0;
        for (int j = 0; j < strlen(_jointData[i].name); j++) {
            if (_jointData[i].name[j] == name[j]) {
                ok++;
            }
        }
        if (ok == strlen(_jointData[i].name)) {
            return i;
        }
    }
    return -1;
}

int NGUnitControl::_getGripperIndex(char* name) {
    for (int i = 0; i < _grippersCount; i++) {
        int ok = 0;
        for (int j = 0; j < strlen(_gripperData[i].name); j++) {
            if (_gripperData[i].name[j] == name[j]) {
                ok++;
            }
        }
        if (ok == strlen(_gripperData[i].name)) {
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
    _writeState();
}

void NGUnitControl::processingLoop() {
    switch (_workMode) {
        case wmNone:
            break;
        case wmObserveMemory:
            observeMemory(OBSERVEMEMORYDELAY);
            break;
        case wmSpec:
            observeMemory(OBSERVEMEMORYDELAY);
            break;
    }
    if (_receivedDataCount > 0) {
        _processingReceivedData();
        _receivedDataCount = 0;
    }
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
    int index = _getEngineIndex(name);
    if (index >= 0) {
        _engines[index]->run(direction);
    }
}

void NGUnitControl::engineStop(char* name) {
    int index = _getEngineIndex(name);
    if (index >= 0) {
        _engines[index]->stop();
    }
}

void NGUnitControl::engineSetSpeed(char* name, int speed) {
    int index = _getEngineIndex(name);
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

int NGUnitControl::jointRead(char* name) {
    int index = _getJointIndex(name);
    if (index >= 0) {
        return _joints[index]->read();
    }
}

int NGUnitControl::jointGetMinRad(char* name) {
    int index = _getJointIndex(name);
    if (index >= 0) {
        return _joints[index]->getMinJointRad();
    }
}

int NGUnitControl::jointGetMaxRad(char* name) {
    int index = _getJointIndex(name);
    if (index >= 0) {
        return _joints[index]->getMaxJointRad();
    }
}

bool NGUnitControl::jointMove(char* name, int targetRad) {
    int index = _getJointIndex(name);
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

void NGUnitControl::jointMoveStepToMax(char* name) {
    int index = _getJointIndex(name);
    if (index >= 0 ) {
        int currentrad = _joints[index]->read();
        if (currentrad < _joints[index]->getMaxJointRad()) {
            int targetrad = currentrad + JOINTMOVESTEP;
            if (targetrad > _joints[index]->getMaxJointRad()) {
                targetrad = _joints[index]->getMaxJointRad();
            }
            _joints[index]->move(targetrad);
        }
    }
}

void NGUnitControl::jointMoveStepToMin(char* name) {
    int index = _getJointIndex(name);
    if (index >= 0 ) {
        int currentrad = _joints[index]->read();
        if (currentrad > _joints[index]->getMinJointRad()) {
            int targetrad = currentrad - JOINTMOVESTEP;
            if (targetrad < _joints[index]->getMinJointRad()) {
                targetrad = _joints[index]->getMinJointRad();
            }
            _joints[index]->move(targetrad);
        }
    }
}

bool NGUnitControl::jointIsMoving(char* name) {
    int index = _getJointIndex(name);
    bool res = index >= 0;
    if (res) {
        res = _jointData[index].targetRad != 0;
    }
    return res;
}

void NGUnitControl::jointSimulate(char* name) {
    int index = _getJointIndex(name);
    if (index >= 0) {
        _joints[index]->simulate();
    }
}

void NGUnitControl::jointSetMaxSpeed(char* name, int speed) {
    int index = _getJointIndex(name);
    if (index >= 0) {
        _joints[index]->setMaxSpeed(speed);
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
    int index = _getGripperIndex(name);
    if (index >= 0) {
        _grippers[index]->grip();
    }
}

void NGUnitControl::gripperRelease(char* name) {
    int index = _getGripperIndex(name);
    if (index >= 0) {
        _grippers[index]->release();
    }
}

void NGUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}
