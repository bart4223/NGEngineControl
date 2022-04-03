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

void NGIrrigationUnitControl::_procesingSecondTick() {
    if ((millis() - _durationSecond) >= 1000) {
        _durationSecond = millis();
        _writeTime();
    }
}

void NGIrrigationUnitControl::_procesingIrrigation() {
    for (int i = 0; i < _irrigationCount; i++) {
        unsigned long interval = _irrigation[i].measuringInterval;
        if ((_irrigation[i].rtLastMeasuring == 0) || ((millis() - _irrigation[i].rtLastMeasuring) >= interval * 1000)) {
            if (_logging) {
                char log[100];
                sprintf(log, "Irrigation %d measure", i);
                writeInfo(log);
            }
            _irrigationMeasure(i);
            _irrigation[i].rtLastMeasuring = millis();
        }
        if (_irrigation[i].rtLastPumpOn != 0) {
            unsigned long interval = _irrigation[i].wateringTime;
            if ((millis() - _irrigation[i].rtLastPumpOn) >= interval * 1000) {
                _pumpOff(_irrigation[i].pump);
                _irrigation[i].rtLastPumpOn = 0;
                if (_logging) {
                    char log[100];
                    char *s;
                    if (_rtc != nullptr) {
                        s = _rtc->getTimeAsText();
                    }
                    sprintf(log, "%s Irr %d hum %d pumpoff", s, i, _getsoilMoistureSensorHumidity(_irrigation[i].soilMoistureSensor));
                    writeInfo(log);
                }
            }
        }
    }
}

void NGIrrigationUnitControl::_irrigationMeasure(int irrigation) {
    char info[100];
    int humidity =_getsoilMoistureSensorHumidity(_irrigation[irrigation].soilMoistureSensor);
    if (humidity > _irrigation[irrigation].desiccationThreshold) {
        _irrigation[irrigation].rtLastPumpOn = millis();
        _irrigation[irrigation].rtLastDesiccationHumidity = humidity;
        _pumpOn(_irrigation[irrigation].pump);
        sprintf(info, "pump on");
    } else {
        sprintf(info, "not dry");
    }
    if (_logging) {
        char log[100];
        char *s;
        if (_rtc != nullptr) {
            s = _rtc->getTimeAsText();
        }
        sprintf(log, "%s Irr %d hum %d %s", s, irrigation, humidity, info);
        writeInfo(log);
    }
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

int NGIrrigationUnitControl::registerIrrigation(byte pinPump, byte pinSoilMoistureSensor, int measuringInterval, int wateringTime, int desiccationThreshold) {
    byte res = _irrigationCount;
    if (_irrigationCount < MAXIRRIGATIONCOUNT) {
        irrigationData id;
        id.pump = registerPump(pinPump);
        id.soilMoistureSensor = registerSoilMoistureSensor(pinSoilMoistureSensor);
        id.measuringInterval = measuringInterval;
        id.wateringTime = wateringTime;
        id.desiccationThreshold = desiccationThreshold;
        id.rtLastMeasuring = 0;
        id.rtLastPumpOn = 0;
        id.rtLastDesiccationHumidity = 0;
        _irrigation[_irrigationCount] = id;
        _irrigationCount++;
    } else {
        _raiseException(ExceptionTooMuchIrrigationCount);
    }
    return res;
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
    _procesingSecondTick();
    _procesingIrrigation();
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
