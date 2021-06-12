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

NGCentralUnitControl::NGCentralUnitControl(char* name, int address) {
    _create(name, address, DEFAULTSERIALRATE);
}

NGCentralUnitControl::NGCentralUnitControl(char* name, int address, int serialRate) {
    _create(name, address, serialRate);
}

void NGCentralUnitControl::_create(char* name, int address, int serialRate) {
    NGCustomUnitControl::_create(name, address, serialRate);
    Wire.begin();
}

int NGCentralUnitControl::_getUnitAddress(char* name) {
    for (int i = 0; i < _unitCount; i++) {
        if (_unit[i].name == name) {
            return _unit[i].address;
        }
    }
    return 0;
}

void NGCentralUnitControl::initialize() {
    if (_logging) {
        char log[100];
        sprintf(log, "...Unit \"%s\" initialized", _name);
        _writeInfo(log);
    }
}

void NGCentralUnitControl::registerUnit(char* name, int address) {
    char log[100];
    unit u;
    u.name = name;
    u.address = address;
    _unit[_unitCount] = u;
    _unitCount++;
    sprintf(log, "Unit %s registered", name);
    _writeInfo(log);
}

void NGCentralUnitControl::processingLoop() {
    
}

void NGCentralUnitControl::sendUnitCommand(char* name, char* command) {
    int address = _getUnitAddress(name);
    if (address > 0) {
        char log[100];
        Wire.beginTransmission(address);
        Wire.write(command);
        Wire.endTransmission();
        _clearInfo();
        sprintf(log, "Command \"%s\" sended", command);
        _writeInfo(log);
    }
}
