//
//  NGDotMatrixWatchCompilationSecondIndicator.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 05.05.25.
//

#ifndef NGDotMatrixWatchCompilationSecondIndicator_h
#define NGDotMatrixWatchCompilationSecondIndicator_h

#include <Arduino.h>
#include <NGIPaintableComponent.h>
#include <Specs/NGCustomWatchComplication.h>

class NGDotMatrixWatchCompilationSecondIndicator : public NGCustomWatchComplication {

private:
    NGIPaintableComponent *_ipc;
    bool _secondIndicator = false;
    
protected:
    void _create(NGIPaintableComponent *ipc);

public:
    NGDotMatrixWatchCompilationSecondIndicator(NGIPaintableComponent *ipc);

    void processingLoop();
};

#endif /* NGDotMatrixWatchCompilationSecondIndicator_h */