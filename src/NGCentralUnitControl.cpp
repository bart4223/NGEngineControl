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

byte NGCentralUnitControl::_getUnitAddress(char* name) {
    for (int i = 0; i < _unitCount; i++) {
        if (_unit[i].name == name) {
            return _unit[i].address;
        }
    }
    return NOADDRESS;
}

void NGCentralUnitControl::initialize() {
    if (_logging) {
        char log[100];
        sprintf(log, "...Unit \"%s\" initialized", _name);
        writeInfo(log);
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

void NGCentralUnitControl::sendUnitCommand(char* name, char* command) {
    char log[100];
    byte address = _getUnitAddress(name);
    clearInfo();
    if (address != NOADDRESS) {
        Wire.beginTransmission(address);
        Wire.write(command);
        Wire.endTransmission();
        sprintf(log, "Command \"%s\" sended", command);
        writeInfo(log);
    } else {
        sprintf(log, "Command \"%s\" NOT sended", command);
        writeInfo(log);
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
