//
//  NGUnitControl.cpp
//  NGUnitControl
//
//  Created by Nils Grimmer on 29.05.21.
//

#include "Wire.h"
#include "NGCommon.h"
#include "NGMemoryObserver.h"
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
    int joint;
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
            joint = _getJointIndex(n);
            if (joint >= 0) {
                _jointData[joint].simulate = !_jointData[joint].simulate;
            }
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
    int gripper;
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
        case CMDOGripperSimulate:
            clearInfo();
            writeInfo((char*)"simulate");
            gripper = _getGripperIndex(n);
            if (gripper >= 0) {
                _gripperData[gripper].simulate = !_gripperData[gripper].simulate;
            }
            break;
    }
    if (n != NULL) {
        free(n);
    }
}

bool NGUnitControl::_processingCommand() {
    bool res = false;
    int readed = 0;
    int index;
    byte input[10];
    while (Serial.available()) {
        input[readed] = Serial.read();
        if (input[readed] != '\n') {
            readed++;
        }
    }
    if (readed >= 1) {
        for (int i = 0; i < _commandCount; i++) {
            if (strlen(_commandData[i].command) == readed) {
                int x = 0;
                for (int j = 0; j < readed; j++) {
                    if (input[j] == _commandData[i].command[j]) {
                        x++;
                    }
                }
                res = x == readed;
                if (res) {
                    switch (_commandData[i].kind) {
                        case ckNone:
                            break;
                        case ckJointSimulate:
                            index = _getJointIndex(_commandData[i].name);
                            if (index >= 0) {
                                _jointData[index].simulate = !_jointData[index].simulate;
                            }
                            break;
                        case ckGripperSimulate:
                            index = _getGripperIndex(_commandData[i].name);
                            if (index >= 0) {
                                _gripperData[index].simulate = !_gripperData[index].simulate;
                            }
                            break;
                    }
                    break;
                }
            }
        }
        if (!res) {
            observeMemory(NODELAY);
        }
    }
    return res;
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
    NGCustomUnitControl::processingLoop();
    switch (_workMode) {
        case wmNone:
            break;
        case wmObserveMemory:
            observeMemory(OBSERVEMEMORYDELAY);
            break;
        case wmCommand:
            if (!_processingCommand()) {
                delay(COMMANDDELAY);
            } else {
                observeMemory(NODELAY);
            }
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
        } else if (_jointData[i].simulate) {
            _joints[i]->simulate();
        }
    }
    for (int i = 0; i < _grippersCount; i++) {
        if (_gripperData[i].simulate) {
            _grippers[i]->simulate();
        }
    }
}

void NGUnitControl::registerCommand(char* command, commandKind kind, char* name) {
    if (_commandCount < COMMANDCOUNT) {
        commandData cd;
        cd.command = command;
        cd.kind = kind;
        cd.name = name;
        _commandData[_commandCount] = cd;
        _commandCount++;
        if (_logging) {
            char log[100];
            sprintf(log, "Command \"%s->%s\" registered", command, name);
            writeInfo(log);
        }
    } else {
        _raiseException(ExceptionTooMuchCommandCount);
    }
}

void NGUnitControl::registerEngine(char* name, NGEngineControl *engine) {
    registerEngine(name, engine, MAXSPEED);
}

void NGUnitControl::registerEngine(char* name, NGEngineControl *engine, int initSpeed) {
    if (_enginesCount < ENGINECOUNT) {
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
    } else {
        _raiseException(ExceptionTooMuchEngineCount);
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
    registerJoint(name, joint, minRad, maxRad, maxMoveTicks, engine, DEFAULTJOINTMOVESTEP);
}

void NGUnitControl::registerJoint(char* name, NGJointControl *joint, int minRad, int maxRad, int maxMoveTicks, int engine, int movestep) {
    if (_jointsCount < JOINTCOUNT) {
        jointData jd;
        jd.name = name;
        jd.minRad = minRad;
        jd.maxRad = maxRad;
        jd.targetRad = 0;
        jd.movestep = movestep;
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
    } else {
        _raiseException(ExceptionTooMuchJointCount);
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

bool NGUnitControl::jointMoveZero(char* name) {
    int index = _getJointIndex(name);
    bool res = index >= 0;
    if (res) {
        res = _joints[index]->moveZero();
    }
    return res;
}

void NGUnitControl::jointMoveStepToMax(char* name) {
    int index = _getJointIndex(name);
    if (index >= 0 ) {
        int currentrad = _joints[index]->read();
        if (currentrad < _joints[index]->getMaxJointRad()) {
            int targetrad = currentrad + _jointData[index].movestep;
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
            int targetrad = currentrad - _jointData[index].movestep;
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

void NGUnitControl::jointSetTransducerThreshold(char* name, int threshold) {
    int index = _getJointIndex(name);
    if (index >= 0) {
        _joints[index]->setTransducerThreshold(threshold);
    }
}

void NGUnitControl::registerGripper(char* name, NGGripperControl *gripper, int minSpeed, int maxSpeed) {
    if (_grippersCount < GRIPPERCOUNT) {
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
    } else {
        _raiseException(ExceptionTooMuchGripperCount);
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

void NGUnitControl::gripperSimulate(char* name) {
    int index = _getGripperIndex(name);
    if (index >= 0) {
        _grippers[index]->simulate();
    }
}

void NGUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}
