//
//  NGVoidMotionMimic.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 06.02.22.
//

#include "NGVoidMotionMimic.h"

NGVoidMotionMimic::NGVoidMotionMimic() {
    _create();
}

void NGVoidMotionMimic::_create() {
    
}

void NGVoidMotionMimic::initialize() {
    
}

motionSequenceKind NGVoidMotionMimic::determineNextMotionSequenceKind(int closeness) {
    return mskNone;
}

bool NGVoidMotionMimic::correctNextMotionSequenceKind() {
    return false;
}

int NGVoidMotionMimic::thinkingDelay() {
    return false;
}

bool NGVoidMotionMimic::nextMotionSequenceNecessary(int closeness) {
    return false;
}

char* NGVoidMotionMimic::getName() {
    return (char*)"Void";
}
