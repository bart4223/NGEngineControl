//
//  NGIrrigationUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.03.22.
//

#include "Wire.h"
#include "NGCommon.h"
#include "NGMemoryObserver.h"
#include "NGIrrigationUnitControl.h"

NGIrrigationUnitControl::NGIrrigationUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE);
}

NGIrrigationUnitControl::NGIrrigationUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE);
}

NGIrrigationUnitControl::NGIrrigationUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE);
}

NGIrrigationUnitControl::NGIrrigationUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate);
}

void NGIrrigationUnitControl::_create(char* name, byte address, int serialRate) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    Wire.begin(_address);
}

void NGIrrigationUnitControl::_initializePumps() {
    for (int i = 0; i < _pumpCount; i++) {
        _pumps[i]->initialize();
    }
}

void NGIrrigationUnitControl::_processingReceivedData() {
    
}

void NGIrrigationUnitControl::_processingStartupLoop() {

}

void NGIrrigationUnitControl::_pumpOn(int pump) {
    _pumps[pump]->on();
}

void NGIrrigationUnitControl::_pumpOff(int pump) {
    _pumps[pump]->off();
}

bool NGIrrigationUnitControl::_isPumpOn(int pump) {
    return _pumps[pump]->isOn();
}

int NGIrrigationUnitControl::_getsoilMoistureSensorHumidity(int soilMoistureSensor) {
    return _soilMoisureSensors[soilMoistureSensor]->getHumidity();
}

void NGIrrigationUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    _initializePumps();
}

long int NGIrrigationUnitControl::startUp() {
    _durationSecond = NGCustomUnitControl::startUp();
    return _durationSecond;
}

int NGIrrigationUnitControl::registerPump(byte pinPump) {
    int res = _pumpCount;
    if (_pumpCount < MAXPUMPCOUNT) {
        _pumps[_pumpCount] = new NGPumpControl(pinPump);
        _pumpCount++;
    }
    if (_logging) {
        char log[100];
        sprintf(log, "Pump %d registered", res);
        writeInfo(log);
    }
    return res;
}

int NGIrrigationUnitControl::registerSoilMoistureSensor(byte pinSoilMoistureSensor) {
    int res = _soilMoistureSensorCount;
    if (_soilMoistureSensorCount < MAXSOILMOISTURESENSORCOUNT) {
        _soilMoisureSensors[_soilMoistureSensorCount] = new NGSoilMoistureSensor(pinSoilMoistureSensor);
        _soilMoistureSensorCount++;
    }
    if (_logging) {
        char log[100];
        sprintf(log, "Soil Sensor %d registered", res);
        writeInfo(log);
    }
    return res;
}

void NGIrrigationUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    // 1s
    if ((millis() - _durationSecond) >= 1000) {
        _durationSecond = millis();
        _writeTime();
    }
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
}

void NGIrrigationUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}
