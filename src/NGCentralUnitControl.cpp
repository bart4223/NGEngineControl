//
//  NGCentralUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 11.06.21.
//

#include "Wire.h"
#include "NGCommon.h"
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
    Wire.begin();
}

void NGCentralUnitControl::_processingReceivedData() {
    
}

byte NGCentralUnitControl::_getUnitAddress(char* name) {
    for (int i = 0; i < _unitCount; i++) {
        if (_unit[i].name == name) {
            return _unit[i].address;
        }
    }
    return NOADDRESS;
}

int NGCentralUnitControl::_prepareCommand(byte subject, byte operation, char* name, int namesize, byte command[]) {
    command[CMDSubject] = subject;
    command[CMDOperation] = operation;
    for (int i = 0; i < namesize; i++) {
        command[i + CMDOffset] = name[i];
    }
    command[namesize + CMDOffset - 1] = CMDNameSeparator;
    return namesize + CMDOffset;
}

void NGCentralUnitControl::initialize() {
    if (_logging) {
        char log[100];
        sprintf(log, "...Unit \"%s\" initialized", _name);
        writeInfo(log);
    }
}

void NGCentralUnitControl::processingLoop() {
    
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

void NGCentralUnitControl::sendUnitGripperGrip(char* name, char* gripper, int grippersize) {
    byte cmd[MaxCMDLength];
    int size = _prepareCommand(CMDSGripper, CMDOGripperGrip, gripper, grippersize, cmd);
    sendUnitCommand(name, cmd, size);
}

void NGCentralUnitControl::sendUnitGripperRelease(char* name, char* gripper, int grippersize) {
    byte cmd[MaxCMDLength];
    int size = _prepareCommand(CMDSGripper, CMDOGripperRelease, gripper, grippersize, cmd);
    sendUnitCommand(name, cmd, size);
}

void NGCentralUnitControl::sendUnitEngineRunForward(char* name, char* engine, int enginesize) {
    byte cmd[MaxCMDLength];
    int size = _prepareCommand(CMDSEngine, CMDOEngineRunForward, engine, enginesize, cmd);
    sendUnitCommand(name, cmd, size);
}

void NGCentralUnitControl::sendUnitEngineRunBackward(char* name, char* engine, int enginesize) {
    byte cmd[MaxCMDLength];
    int size = _prepareCommand(CMDSEngine, CMDOEngineRunBackward, engine, enginesize, cmd);
    sendUnitCommand(name, cmd, size);
}

void NGCentralUnitControl::sendUnitEngineStop(char* name, char* engine, int enginesize) {
    byte cmd[MaxCMDLength];
    int size = _prepareCommand(CMDSEngine, CMDOEngineStop, engine, enginesize, cmd);
    sendUnitCommand(name, cmd, size);
}

void NGCentralUnitControl::sendUnitCommand(char* name, byte command[], int commandsize) {
    byte address = _getUnitAddress(name);
    clearInfo();
    if (address != NOADDRESS) {
        Wire.beginTransmission(address);
        Wire.write(command, commandsize);
        Wire.endTransmission();
    }
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
