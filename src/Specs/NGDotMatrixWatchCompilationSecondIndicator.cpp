//
//  NGDotMatrixWatchCompilationSecondIndicator.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 05.05.25.
//

#include <Specs/NGDotMatrixWatchCompilationSecondIndicator.h>

NGDotMatrixWatchCompilationSecondIndicator::NGDotMatrixWatchCompilationSecondIndicator(NGIPaintableComponent *ipc) {
    _create(ipc);
}

void NGDotMatrixWatchCompilationSecondIndicator::_create(NGIPaintableComponent *ipc) {
    _ipc = ipc;
}

void NGDotMatrixWatchCompilationSecondIndicator::processingLoop() {
    _secondIndicator = !_secondIndicator;
    if (_secondIndicator) {
        _ipc->drawPoint(_ipc->getWidth() / 2 - 1, _ipc->getHeight() - 1, COLOR_RED);
    } else {
        _ipc->clearPoint(_ipc->getWidth() / 2 - 1, _ipc->getHeight() - 1);
    }
}