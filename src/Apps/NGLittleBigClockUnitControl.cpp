//
//  NGLittleBigClockUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.04.25.
//

#include <Apps/NGLittleBigClockUnitControl.h>

NGLittleBigClockUnitControl::NGLittleBigClockUnitControl() {
    _create(NONAME, NOADDRESS, DEFAULTSERIALRATE);
}

NGLittleBigClockUnitControl::NGLittleBigClockUnitControl(char* name) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE);
}

NGLittleBigClockUnitControl::NGLittleBigClockUnitControl(char* name, byte address) {
    _create(name, address, DEFAULTSERIALRATE);
}

NGLittleBigClockUnitControl::NGLittleBigClockUnitControl(char* name, byte address, int serialRate) {
    _create(name, address, serialRate);
}

void NGLittleBigClockUnitControl::_create(char* name, byte address, int serialRate) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    Wire.begin(_address);
}

void NGLittleBigClockUnitControl::_processingReceivedData() {
    
}

void NGLittleBigClockUnitControl::_processingStartupLoop() {

}

void NGLittleBigClockUnitControl::_processingIRRemoteData() {
    
}

void NGLittleBigClockUnitControl::registerWatchDial(NGCustomWatchDial *watchdial) {
    _watchDial = watchdial;
}

void NGLittleBigClockUnitControl::initialize() {
    NGCustomUnitControl::initialize();
    if (_watchDial != nullptr) {
        _watchDial->initialize();
    }
    _lastRefresh = millis();
}

void NGLittleBigClockUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    if (_watchDial != nullptr) {
        _watchDial->processingLoop();
        if (millis() - _lastRefresh > DEFWATCHDELAY || !_initWatchDial) {
            if (_rtc != nullptr) {
                DateTime now = _rtc->getNow();
                _watchDial->setTime(now.hour(), now.minute(), now.second());
            }
            _initWatchDial = true;
            _lastRefresh = millis();
        }
    }
}

void NGLittleBigClockUnitControl::invalidWatchDial() {
    _initWatchDial = false;
}

void NGLittleBigClockUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}