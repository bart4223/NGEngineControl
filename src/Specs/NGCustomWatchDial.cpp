//
//  NGCustomWatchDial.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 27.04.25.
//

#include <Specs/NGCustomWatchDial.h>

void NGCustomWatchDial::_create(NGIPaintableComponent *ipc) {
    _ipc = ipc;
}

void NGCustomWatchDial::registerComplication(NGCustomWatchComplication *complication, int delay) {
    if (_complicationCount < MAXWATCHCOMPLICATIONS) {
        _complications[_complicationCount].complication = complication;
        _complications[_complicationCount].delay = delay;
        _complications[_complicationCount].lastUpdate = 0;
        _complicationCount++;
    }
}

void NGCustomWatchDial::processingLoop() {
    for (byte i = 0; i < _complicationCount; i++) {
        if (millis() - _complications[i].lastUpdate > _complications[i].delay) {
            _complications[i].complication->processingLoop();
            _complications[i].lastUpdate = millis();
        }
    }
}