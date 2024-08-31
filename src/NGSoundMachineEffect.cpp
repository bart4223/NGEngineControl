//
//  NGSoundMachineEffect.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 31.08.24.
//

#include "NGSoundMachineEffect.h"

NGSoundMachineEffect::NGSoundMachineEffect(NGSoundMachine *soundmachine) {
    _create(soundmachine);
}

void NGSoundMachineEffect::_create(NGSoundMachine *soundmachine) {
    _soundMachine = soundmachine;
}

void NGSoundMachineEffect::initialize() {
    
}

void NGSoundMachineEffect::playJingle(byte jingle) {
    _jingle = jingle;
}

void NGSoundMachineEffect::processingLoop() {
    if (_jingle != NOJINGLE) {
        _soundMachine->play(_jingle);
        _jingle = NOJINGLE;
    }
    _soundMachine->processingLoop();
}
