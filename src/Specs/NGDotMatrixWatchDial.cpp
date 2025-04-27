//
//  NGDotMatrixWatchDial.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.04.25.
//

#include <Specs/NGDotMatrixWatchDial.h>

NGDotMatrixWatchDial::NGDotMatrixWatchDial(NGIPaintableComponent *ipc) {
    _create(ipc);
}

void NGDotMatrixWatchDial::registerDecimalDigitHour(NGColorDotMatrixDecimalDigit *digitOne, NGColorDotMatrixDecimalDigit *digitTens) {
    _digitHourOne = digitOne;
    _digitHourTens = digitTens;
}
    
void NGDotMatrixWatchDial::registerDecimalDigitMinute(NGColorDotMatrixDecimalDigit *digitOne, NGColorDotMatrixDecimalDigit *digitTens) {
    _digitMinuteOne = digitOne;
    _digitMinuteTens = digitTens;
}

void NGDotMatrixWatchDial::registerDecimalDigitSecond(NGColorDotMatrixDecimalDigit *digitOne, NGColorDotMatrixDecimalDigit *digitTens) {
    _digitSecondOne = digitOne;
    _digitSecondTens = digitTens;
}   

void NGDotMatrixWatchDial::initialize() {
    if (_digitHourOne != nullptr) {
        _digitHourOne->setValue(0);
    }
    if (_digitHourTens != nullptr) {
        _digitHourTens->setValue(0);
    }
    if (_digitMinuteOne != nullptr) {
        _digitMinuteOne->setValue(0);
    }
    if (_digitMinuteTens != nullptr) {
        _digitMinuteTens->setValue(0);
    }
    if (_digitSecondOne != nullptr) {
        _digitSecondOne->setValue(0);
    }
    if (_digitSecondTens != nullptr) {
        _digitSecondTens->setValue(0);
    }
}

void NGDotMatrixWatchDial::setHour(int hour) {
    if (_digitHourOne != nullptr) {
        _digitHourOne->setValue(hour % 10);
    }
    if (_digitHourTens != nullptr) {
        _digitHourTens->setValue(hour / 10);
    }
}

void NGDotMatrixWatchDial::setMinute(int minute) {
    if (_digitMinuteOne != nullptr) {
        _digitMinuteOne->setValue(minute % 10);
    }
    if (_digitMinuteTens != nullptr) {
        _digitMinuteTens->setValue(minute / 10);
    }
}

void NGDotMatrixWatchDial::setSecond(int second) {
    if (_digitSecondOne != nullptr) {
        _digitSecondOne->setValue(second % 10);
    }
    if (_digitSecondTens != nullptr) {
        _digitSecondTens->setValue(second / 10);
    }
    _secondIndicator = !_secondIndicator;
    if (_secondIndicator) {
        _ipc->drawPoint(_ipc->getWidth() - 1, _ipc->getHeight() - 1, COLOR_RED);
    } else {
        _ipc->clearPoint(_ipc->getWidth() - 1, _ipc->getHeight() - 1);
    }
}

void NGDotMatrixWatchDial::setTime(int hour, int minute, int second) {
    setHour(hour);
    setMinute(minute);
    setSecond(second);
}