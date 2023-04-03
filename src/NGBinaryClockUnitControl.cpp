//
//  NGBinaryClockUnitControl.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.10.22.
//

#include "Wire.h"
#include "NGMemoryObserver.h"
#include "NGBinaryClockUnitControl.h"

NGBinaryClockUnitControl::NGBinaryClockUnitControl(char* name, NGIPaintableComponent *cdm) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE, cdm, DEFBINARYCLOCKPOSX, DEFBINARYCLOCKPOSY);
}

NGBinaryClockUnitControl::NGBinaryClockUnitControl(char* name, NGIPaintableComponent *cdm,  byte posX, byte posY) {
    _create(name, NOADDRESS, DEFAULTSERIALRATE, cdm, posX, posY);
}

void NGBinaryClockUnitControl::_create(char* name, byte address, int serialRate, NGIPaintableComponent *cdm, byte posX, byte posY) {
    NGCustomUnitControl::_create(name, address, serialRate);
    _version = VERSION;
    if (_address != NOADDRESS) {
        Wire.begin(_address);
    }
    _cdm = cdm;
    registerRealTimeClock(new NGRealTimeClock());
    byte arity;
    byte offset = 0;
    for (int i = 0; i < DIGITCOUNT; i++) {
        switch(i) {
            case 0:
                arity = 2;
                break;
            case 2:
            case 4:
                arity = 3;
                break;
            default:
                arity = 4;
                break;
        }
        if (_withArityOffset) {
            offset = i / 2;
        }
        _digits[i] = new NGColorDotMatrixBinaryDigit(_cdm, arity, i + posX + offset, posY);
    }
}

void NGBinaryClockUnitControl::_processingReceivedData() {
    
}

void NGBinaryClockUnitControl::_processingStartupLoop() {

}

void NGBinaryClockUnitControl::_processingIRRemoteData() {
    
}

void NGBinaryClockUnitControl::_processingClock() {
    _cdm->beginUpdate();
    DateTime now = _rtc->getNow();
    for (int i = 0; i < DIGITCOUNT; i++) {
        switch(i) {
            case 0:
                _digits[i]->setValue(now.hour() / 10);
                break;
            case 1:
                _digits[i]->setValue(now.hour() % 10);
                break;
            case 2:
                _digits[i]->setValue(now.minute() / 10);
                break;
            case 3:
                _digits[i]->setValue(now.minute() % 10);
                break;
            case 4:
                _digits[i]->setValue(now.second() / 10);
                break;
            case 5:
                _digits[i]->setValue(now.second() % 10);
                break;
        }
    }
    _cdm->endUpdate();
}

void NGBinaryClockUnitControl::initialize() {
    _rtc->initialize(_adjustRTC);
    _cdm->beginUpdate();
    for (int i = 0; i < DIGITCOUNT; i++) {
        _digits[i]->setValue(0);
    }
    _cdm->endUpdate();
}

void NGBinaryClockUnitControl::setAdjustRTC(bool adjustRTC) {
    _adjustRTC = adjustRTC;
}

void NGBinaryClockUnitControl::setColorOff(colorRGB color) {
    for (int i = 0; i < DIGITCOUNT; i++) {
        _digits[i]->setColorOff(color);
    }
}

void NGBinaryClockUnitControl::setColorOn(colorRGB color) {
    for (int i = 0; i < DIGITCOUNT; i++) {
        _digits[i]->setColorOn(color);
    }
}

void NGBinaryClockUnitControl::setOffset(int offsetX, int offsetY) {
    for (int i = 0; i < DIGITCOUNT; i++) {
        _digits[i]->setOffset(offsetX * i, offsetY);
    }
}

void NGBinaryClockUnitControl::processingLoop() {
    NGCustomUnitControl::processingLoop();
    _processingClock();
    switch (_workMode) {
        case wmNone:
            break;
        case wmObserveMemory:
        case wmSpec:
            if (millis() - _lastMemoryObserved > OBSERVEMEMORYDELAY) {
                observeMemory(0);
                _lastMemoryObserved = millis();
            }
            break;
    }
}

void NGBinaryClockUnitControl::requestData(byte* data) {
    memcpy(data, _requestedData, REQUESTEDDATALENGTH);
}
