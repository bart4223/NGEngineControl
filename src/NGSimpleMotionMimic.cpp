//
//  NGSimpleMotionMimic.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 03.06.23.
//

#include "NGSimpleMotionMimic.h"

NGSimpleMotionMimic::NGSimpleMotionMimic() {
    _create();
}

void NGSimpleMotionMimic::_create() {
    
}

void NGSimpleMotionMimic::initialize() {
    
}

motionSequenceKind NGSimpleMotionMimic::determineNextMotionSequenceKind(int closeness) {
    return mskStop;
}

bool NGSimpleMotionMimic::correctNextMotionSequenceKind() {
    return false;
}

int NGSimpleMotionMimic::thinkingDelay() {
    return false;
}

bool NGSimpleMotionMimic::nextMotionSequenceNecessary(int closeness) {
    return true;
}

char* NGSimpleMotionMimic::getName() {
    return (char*)"Simple";
}
