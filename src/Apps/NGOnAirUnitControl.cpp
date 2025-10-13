//
//  NGOnAirUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.06.25.
//

#include <Apps/NGOnAirUnitControl.h>
#include <NGExceptionDefinitions.h>

NGOnAirUnitControl::NGOnAirUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE);
}

NGOnAirUnitControl::NGOnAirUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE);
}

NGOnAirUnitControl::NGOnAirUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE);
}

NGOnAirUnitControl::NGOnAirUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate);
}

void NGOnAirUnitControl::_create(char* name, byte address, int serialRate) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    Wire.begin(_address);
}

void NGOnAirUnitControl::_processingReceivedData() {
    
}

void NGOnAirUnitControl::_processingStartupLoop() {

}

void NGOnAirUnitControl::_processingIRRemoteData() {
    
}

void NGOnAirUnitControl::_observeTemperature() {
    if (_oneWireTemperatureSensor != nullptr) {
        char log[100];
        char temp_str[10];
        dtostrf(_oneWireTemperatureSensor->getTemperatureAsFloat(), 4, 1, temp_str);
        if(_indicator) {
            sprintf(log, "%s:GradCelsius", temp_str);  
        } else {
            sprintf(log, "%s GradCelsius", temp_str);
        }
        writeInfo(log);
        _indicator = !_indicator;
    }            
}

byte NGOnAirUnitControl::registerEffect(NGIEffect *effect) {
    if (_effectCount < MAXEFFECTCOUNT) {
        int res = _effectCount;
        _effects[res] = effect;
        _effectCount++;
        return res;
    } else {
        _raiseException(ExceptionTooMuchEffectCount);
    }
    return -1;
}

void NGOnAirUnitControl::registerOneWireTemperatureSensor(NGOneWireTemperatureSensor *sensor) {
    _oneWireTemperatureSensor = sensor;
}

void NGOnAirUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    for (int i = 0; i < _effectCount; i++) {
        _effects[i]->initialize();
    }
    if (_oneWireTemperatureSensor != nullptr) {
        _oneWireTemperatureSensor->initialize();
    }
    _lastTemperatureObserved = millis();
}

void NGOnAirUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    if (_currentEffectIndex >= 0 && _currentEffectIndex < _effectCount) {
        _effects[_currentEffectIndex]->processingLoop();
    }
    if (_currentEffectIndex < 1) {
        if (millis() - _lastTemperatureObserved > DEFTEMPERATUREOBSERVETIME) {
            _observeTemperature();
            _lastTemperatureObserved = millis();
        }
    }
}

void NGOnAirUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}

void NGOnAirUnitControl::setCurrentEffect(int effectIndex) {
    _currentEffectIndex = effectIndex;
}