//
//  NGQuestionDialog.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.12.21.
//

#include "NGQuestionDialog.h"

NGQuestionDialog::NGQuestionDialog(byte pinYes, byte pinNo) {
    _create(pinYes, pinNo, DLGQMAXDELAY);
}

NGQuestionDialog::NGQuestionDialog(byte pinYes, byte pinNo, int delay) {
    _create(pinYes, pinNo, delay);
}

void NGQuestionDialog::_create(byte pinYes, byte pinNo, int delay) {
    _pinYes = pinYes;
    _pinNo = pinNo;
    _delay = delay;
}

void NGQuestionDialog::initialize() {
    pinMode(_pinYes, INPUT_PULLUP);
    pinMode(_pinNo, INPUT_PULLUP);
}

void NGQuestionDialog::setDelay(int delay) {
    _delay = delay;
}

bool NGQuestionDialog::confirm() {
    bool res = false;
    bool doBreak = false;
    while(!doBreak) {
        doBreak = !digitalRead(_pinYes);
        if (doBreak) {
            res = true;
        } else {
            doBreak = !digitalRead(_pinNo);
        }
    }
    if (_delay > 0) {
        delay(_delay);
    }
    return res;
}
