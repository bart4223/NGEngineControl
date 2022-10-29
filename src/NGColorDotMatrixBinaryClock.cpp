//
//  NGColorDotMatrixBinaryClock.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 29.10.22.
//

#include "NGColorDotMatrixBinaryClock.h"

NGColorDotMatrixBinaryClock::NGColorDotMatrixBinaryClock(NGColorDotMatrix *cdm) {
    _create(cdm, DEFBINARYCLOCKPOSX, DEFBINARYCLOCKPOSY);
}

NGColorDotMatrixBinaryClock::NGColorDotMatrixBinaryClock(NGColorDotMatrix *cdm,  byte posX, byte posY) {
    _create(cdm, posX, posY);
}

void NGColorDotMatrixBinaryClock::_create(NGColorDotMatrix *cdm, byte posX, byte posY) {
    _cdm = cdm;
    _rtc = new NGRealTimeClock();
    byte arity;
    for (int i = 0; i < DIGITCOUNT; i++) {
        if (i == 0) {
            arity = 2;
        } else if (i == 2 || i == 4) {
            arity = 3;
        } else {
            arity = 4;
        }
        _digits[i] = new NGColorDotMatrixBinaryDigit(_cdm, arity, i + posX, posY);
    }
}

void NGColorDotMatrixBinaryClock::initialize() {
    _rtc->initialize();
    _cdm->initialize();
    _cdm->beginUpdate();
    for (int i = 0; i < DIGITCOUNT; i++) {
        _digits[i]->setValue(0);
    }
    _cdm->endUpdate();
}

void NGColorDotMatrixBinaryClock::setColorOff(colorRGB color) {
    for (int i = 0; i < DIGITCOUNT; i++) {
        _digits[i]->setColorOff(color);
    }
}

void NGColorDotMatrixBinaryClock::setColorOn(colorRGB color) {
    for (int i = 0; i < DIGITCOUNT; i++) {
        _digits[i]->setColorOn(color);
    }
}

void NGColorDotMatrixBinaryClock::processingLoop() {
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
    delay(DEFBINARYCLOCKDELAY);
}
