//
//  NGCurrentMeasurementUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 19.07.22.
//

#include "Wire.h"
#include "NGCommon.h"
#include "NGMemoryObserver.h"
#include "NGCurrentMeasurementUnitControl.h"

NGCurrentMeasurementUnitControl::NGCurrentMeasurementUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE);
}

NGCurrentMeasurementUnitControl::NGCurrentMeasurementUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE);
}

NGCurrentMeasurementUnitControl::NGCurrentMeasurementUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE);
}

NGCurrentMeasurementUnitControl::NGCurrentMeasurementUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate);
}

void NGCurrentMeasurementUnitControl::_create(char* name, byte address, int serialRate) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    Wire.begin(_address);
}

void NGCurrentMeasurementUnitControl::_initializeSensors() {
    for (int i = 0; i < _sensorCount; i++) {
        _currentSensors[i].currentSensor->initialize();
    }
}

void NGCurrentMeasurementUnitControl::_processingReceivedData() {
    
}

void NGCurrentMeasurementUnitControl::_processingStartupLoop() {

}

void NGCurrentMeasurementUnitControl::_procesingCurrentSensors() {
    for (int i = 0; i < _sensorCount; i++) {
        if ((millis() - _currentSensors[i].lastTick) >= _currentSensors[i].delay) {
            _currentSensors[i].lastTick = millis();
            _currentSensors[i].current = _currentSensors[i].currentSensor->getCurrent();
            _currentSensors[i].min = _currentSensors[i].currentSensor->getMin();
            _currentSensors[i].max = _currentSensors[i].currentSensor->getMax();
        }
    }
}

void NGCurrentMeasurementUnitControl::_displayCurrentSensors() {
    if ((millis() - _secondTick) >= _displaySensorInterval) {
        _secondTick = millis();
        if (_displayedSensor >= 0) {
            char log[100];
            sprintf(log, "S%d: min %dmA, max %dmA, %dmA", _displayedSensor, _currentSensors[_displayedSensor].min, _currentSensors[_displayedSensor].max, _currentSensors[_displayedSensor].current);
            int len = strlen(log);
            if (_lastInfoLen > len) {
                for (int j = len; j < _lastInfoLen; j++) {
                    log[j] = ' ';
                }
                log[_lastInfoLen] = '\0';
            }
            _lastInfoLen = len;
            writeInfo(log);
            _displayedSensor++;
            if (_displayedSensor >= _sensorCount) {
                _displayedSensor = 0;
            }
        }
    }
}

void NGCurrentMeasurementUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    _initializeSensors();
}

void NGCurrentMeasurementUnitControl::setDisplaySensorInterval(int interval) {
    _displaySensorInterval = interval;
}

int NGCurrentMeasurementUnitControl::registerSensor(CurrentSensorTechnology sensorTechnology, byte pinSensor, int delay) {
    int res = _sensorCount;
    if (_sensorCount < MAXCURRENTSENSORCOUNT) {
        currentSensorData csd;
        csd.currentSensor = new NGCurrentSensor(sensorTechnology, pinSensor);
        csd.delay = delay;
        _currentSensors[_sensorCount] = csd;
        _sensorCount++;
    }
    if (_displayedSensor == -1) {
        _displayedSensor++;
    }
    if (_logging) {
        char log[100];
        sprintf(log, "Current Sensor %d registered", res);
        writeInfo(log);
    }
    return res;
}

void NGCurrentMeasurementUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    _procesingCurrentSensors();
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
    _displayCurrentSensors();
}

void NGCurrentMeasurementUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}
