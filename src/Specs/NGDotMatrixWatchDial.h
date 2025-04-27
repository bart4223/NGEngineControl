//
//  NGDotMatrixWatchDial.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.04.25.
//

#ifndef NGDotMatrixWatchDial_h
#define NGDotMatrixWatchDial_h

#include <Arduino.h>
#include <Specs/NGCustomWatchDial.h>
#include <NGColorDotMatrixDecimalDigit.h>

class NGDotMatrixWatchDial : public NGCustomWatchDial {

private:
    bool _secondIndicator = false;
    NGColorDotMatrixDecimalDigit *_digitHourOne = nullptr;
    NGColorDotMatrixDecimalDigit *_digitHourTens = nullptr;
    NGColorDotMatrixDecimalDigit *_digitMinuteOne = nullptr;
    NGColorDotMatrixDecimalDigit *_digitMinuteTens = nullptr;
    NGColorDotMatrixDecimalDigit *_digitSecondOne = nullptr;
    NGColorDotMatrixDecimalDigit *_digitSecondTens = nullptr;  

public:
    NGDotMatrixWatchDial(NGIPaintableComponent *ipc);

    void registerDecimalDigitHour(NGColorDotMatrixDecimalDigit *digitOne, NGColorDotMatrixDecimalDigit *digitTens);
    
    void registerDecimalDigitMinute(NGColorDotMatrixDecimalDigit *digitOne, NGColorDotMatrixDecimalDigit *digitTens);

    void registerDecimalDigitSecond(NGColorDotMatrixDecimalDigit *digitOne, NGColorDotMatrixDecimalDigit *digitTens);

    void initialize();

    void setHour(int hour);

    void setMinute(int minute);

    void setSecond(int second);

    void setTime(int hour, int minute, int second);
};

#endif /* NGDotMatrixWatchDialh */