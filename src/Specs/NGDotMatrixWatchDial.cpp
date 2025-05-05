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
}

void NGDotMatrixWatchDial::setTime(int hour, int minute, int second) {
    setHour(hour);
    setMinute(minute);
    setSecond(second);
}

void NGDotMatrixWatchDial::setDecimalDigitHourPosition(int xTen, int yTen, int xOne, int yOne) {
    if (_digitHourTens != nullptr) {
        _digitHourTens->setPosX(xTen);
        _digitHourTens->setPosY(yTen);
    }
    if (_digitHourOne != nullptr) {
        _digitHourOne->setPosX(xOne);
        _digitHourOne->setPosY(yOne);
    }
}

void NGDotMatrixWatchDial::setDecimalDigitMinutePosition(int xTen, int yTen, int xOne, int yOne) {
    if (_digitMinuteTens != nullptr) {
        _digitMinuteTens->setPosX(xTen);
        _digitMinuteTens->setPosY(yTen);
    }
    if (_digitMinuteOne != nullptr) {
        _digitMinuteOne->setPosX(xOne);
        _digitMinuteOne->setPosY(yOne);
    }
}
    
void NGDotMatrixWatchDial::setDecimalDigitSecondPosition(int xTen, int yTen, int xOne, int yOne) {
    if (_digitSecondTens != nullptr) {
        _digitSecondTens->setPosX(xTen);
        _digitSecondTens->setPosY(yTen);
    }
    if (_digitSecondOne != nullptr) {
        _digitSecondOne->setPosX(xOne);
        _digitSecondOne->setPosY(yOne);
    }
}

void NGDotMatrixWatchDial::setDecimalDigitHourFont(NGCustomFont *fontTen, NGCustomFont *fontOne) {
    if (_digitHourTens != nullptr) {
        _digitHourTens->setFont(fontTen);
    }
    if (_digitHourOne != nullptr) {
        _digitHourOne->setFont(fontOne);
    }
}
    
void NGDotMatrixWatchDial::setDecimalDigitMinuteFont(NGCustomFont *fontTen, NGCustomFont *fontOne) {
    if (_digitMinuteTens != nullptr) {
        _digitMinuteTens->setFont(fontTen);
    }
    if (_digitMinuteOne != nullptr) {
        _digitMinuteOne->setFont(fontOne);
    }
}

void NGDotMatrixWatchDial::setDecimalDigitSecondFont(NGCustomFont *fontTen, NGCustomFont *fontOne) {
    if (_digitSecondTens != nullptr) {
        _digitSecondTens->setFont(fontTen);
    }
    if (_digitSecondOne != nullptr) {
        _digitSecondOne->setFont(fontOne);
    }
}