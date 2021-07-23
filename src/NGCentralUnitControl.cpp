//
//  NGCentralUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 11.06.21.
//

#include "Wire.h"
#include "NGCommon.h"
#include "NGMemoryObserver.h"
#include "NGCentralUnitControl.h"

NGCentralUnitControl::NGCentralUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE);
}

NGCentralUnitControl::NGCentralUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE);
}

NGCentralUnitControl::NGCentralUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE);
}

NGCentralUnitControl::NGCentralUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate);
}

void NGCentralUnitControl::_create(char* name, byte address, int serialRate) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = (char*)"0.3";
    Wire.begin();
}

void NGCentralUnitControl::_processingReceivedData() {
    
}

void NGCentralUnitControl::_processingIRRemoteData() {
    for (int i = 0; i < _irremotefuncCount; i++) {
        if (_irremotefunc[i].protocol == _irremotedata.protocol && _irremotefunc[i].address == _irremotedata.address
                && _irremotefunc[i].command == _irremotedata.command) {
            switch (_irremotefunc[i].type) {
                case ftMenu:
                    _currentComponent++;
                    if (_currentComponent > _componentCount - 1) {
                        _currentComponent = 0;
                        if (_componentCount == 0) {
                            _currentComponent = -1;
                        }
                    }
                    clearInfo();
                    if (_currentComponent >= 0) {
                        char log[100];
                        sprintf(log, "%s.%s", _component[_currentComponent].unit, _component[_currentComponent].component);
                        writeInfo(log);
                    }
                    break;
                case ftLeft:
                    if (_currentComponent >= 0) {
                        switch (_component[_currentComponent].type) {
                            case ctJoint:
                                sendUnitJointMoveStepToMin(_component[_currentComponent].unit, _component[_currentComponent].component);
                                break;
                            case ctGripper:
                                sendUnitGripperGrip(_component[_currentComponent].unit, _component[_currentComponent].component);
                                break;
                        }
                    }
                    break;
                case ftRight:
                    if (_currentComponent >= 0) {
                        switch (_component[_currentComponent].type) {
                            case ctJoint:
                                sendUnitJointMoveStepToMax(_component[_currentComponent].unit, _component[_currentComponent].component);
                                break;
                            case ctGripper:
                                sendUnitGripperRelease(_component[_currentComponent].unit, _component[_currentComponent].component);
                                break;
                        }
                    }
                    break;
            }
        }
    }
}

byte NGCentralUnitControl::_getUnitAddress(char* name) {
    for (int i = 0; i < _unitCount; i++) {
        if (_unit[i].name == name) {
            return _unit[i].address;
        }
    }
    return NOADDRESS;
}

int NGCentralUnitControl::_prepareCommand(byte subject, byte operation, char* name, byte command[]) {
    command[CMDSubject] = subject;
    command[CMDOperation] = operation;
    for (int i = 0; i < strlen(name); i++) {
        command[i + CMDOffset] = name[i];
    }
    command[strlen(name) + CMDOffset] = CMDNameSeparator;
    return strlen(name) + CMDOffset + 1;
}

void NGCentralUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    if (_logging) {
        char log[100];
        sprintf(log, "...Unit \"%s\" initialized", _name);
        writeInfo(log);
    }
    _writeState();
}

void NGCentralUnitControl::processingLoop() {
    if (_irremotedataReceived) {
        _processingIRRemoteData();
        _irremotedataReceived = false;
    }
    switch (_workMode) {
        case wmNone:
            break;
        case wmObserveMemory:
            observeMemory(5000);
            break;
        case wmSpec:
            observeMemory(5000);
            break;
    }
}

void NGCentralUnitControl::registerUnit(char* name, byte address) {
    char log[100];
    unit u;
    u.name = name;
    u.address = address;
    _unit[_unitCount] = u;
    _unitCount++;
    sprintf(log, "Unit %s registered", name);
    writeInfo(log);
}

void NGCentralUnitControl::registerComponent(componentType type, char* unit, char* comp) {
    component c;
    c.unit = unit;
    c.component = comp;
    c.type = type;
    _component[_componentCount] = c;
    _componentCount++;
}

void NGCentralUnitControl::registerIRRemoteFunction(functionType type, byte protocol, byte address, byte command) {
    irremotefunc func;
    func.protocol = protocol;
    func.address = address;
    func.command = command;
    func.type = type;
    _irremotefunc[_irremotefuncCount] = func;
    _irremotefuncCount++;
}

void NGCentralUnitControl::sendUnitGripperGrip(char* name, char* gripper) {
    byte cmd[MaxCMDLength];
    int size = _prepareCommand(CMDSGripper, CMDOGripperGrip, gripper, cmd);
    sendUnitCommand(name, cmd, size);
}

void NGCentralUnitControl::sendUnitGripperRelease(char* name, char* gripper) {
    byte cmd[MaxCMDLength];
    int size = _prepareCommand(CMDSGripper, CMDOGripperRelease, gripper, cmd);
    sendUnitCommand(name, cmd, size);
}

void NGCentralUnitControl::sendUnitEngineRunForward(char* name, char* engine) {
    byte cmd[MaxCMDLength];
    int size = _prepareCommand(CMDSEngine, CMDOEngineRunForward, engine, cmd);
    sendUnitCommand(name, cmd, size);
}

void NGCentralUnitControl::sendUnitEngineRunBackward(char* name, char* engine) {
    byte cmd[MaxCMDLength];
    int size = _prepareCommand(CMDSEngine, CMDOEngineRunBackward, engine, cmd);
    sendUnitCommand(name, cmd, size);
}

void NGCentralUnitControl::sendUnitEngineStop(char* name, char* engine) {
    byte cmd[MaxCMDLength];
    int size = _prepareCommand(CMDSEngine, CMDOEngineStop, engine, cmd);
    sendUnitCommand(name, cmd, size);
}

void NGCentralUnitControl::sendUnitEngineSetSpeed(char* name, char* engine, int speed) {
    byte cmd[MaxCMDLength];
    int size = _prepareCommand(CMDSEngine, CMDOEngineSetSpeed, engine, cmd);
    cmd[size] = speed;
    sendUnitCommand(name, cmd, size + 1);
}

void NGCentralUnitControl::sendUnitJointMove(char* name, char* joint, int targetrad) {
    byte cmd[MaxCMDLength];
    int size = _prepareCommand(CMDSJoint, CMDOJointMove, joint, cmd);
    cmd[size] = targetrad >> 8;
    cmd[size + 1] = targetrad;
    sendUnitCommand(name, cmd, size + 2);
}

void NGCentralUnitControl::sendUnitJointSimulate(char* name, char* joint) {
    byte cmd[MaxCMDLength];
    int size = _prepareCommand(CMDSJoint, CMDOJointSimulate, joint, cmd);
    sendUnitCommand(name, cmd, size);
}

void NGCentralUnitControl::sendUnitJointMoveStepToMax(char* name, char* joint) {
    byte cmd[MaxCMDLength];
    int size = _prepareCommand(CMDSJoint, CMDOJointMoveStepToMax, joint, cmd);
    sendUnitCommand(name, cmd, size);
}

void NGCentralUnitControl::sendUnitJointMoveStepToMin(char* name, char* joint) {
    byte cmd[MaxCMDLength];
    int size = _prepareCommand(CMDSJoint, CMDOJointMoveStepToMin, joint, cmd);
    sendUnitCommand(name, cmd, size);
}

int NGCentralUnitControl::receiveUnitJointRead(char* name, char* joint) {
    byte cmd[MaxCMDLength];
    int size = _prepareCommand(CMDSJoint, CMDOJointRead, joint, cmd);
    if (sendUnitCommand(name, cmd, size)) {
        receiveUnitData(name);
        if (_receivedDataCount == 2) {
            return (_receivedData[0] << 8) | (_receivedData[1]);
        }
    }
    return -1;
}

bool NGCentralUnitControl::sendUnitCommand(char* name, byte command[], int commandsize) {
    byte address = _getUnitAddress(name);
    bool res = address != NOADDRESS;
    if (res) {
        Wire.beginTransmission(address);
        Wire.write(command, commandsize);
        Wire.endTransmission();
    }
    return res;
}

void NGCentralUnitControl::receiveUnitData(char* name) {
    byte address = _getUnitAddress(name);
    clearInfo();
    if (address != NOADDRESS) {
        Wire.requestFrom((int)address, 2); // Read 2 Bytes
        receiveDataStart();
        int i = 0;
        while(Wire.available()) {
            receivedData(i, Wire.read());
            i++;
        }
        receiveDataFinish(i);
    }
}

void NGCentralUnitControl::requestData(byte* data) {
    data[0] = 0x34; //4
    data[1] = 0x32; //2
}

void NGCentralUnitControl::setIRRemoteData(byte protocol, byte address, byte command) {
    _irremotedata.protocol = protocol;
    _irremotedata.address = address;
    _irremotedata.command = command;
    _irremotedataReceived = true;
}
