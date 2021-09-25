//
//  NGSoundMachine.cpp
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.09.21.
//

#include "NGCustomJingle.h"
#include "NGSoundMachine.h"

NGSoundMachine::NGSoundMachine() {
    _create(DEFPINPIEZO);
}

NGSoundMachine::NGSoundMachine(int pinPiezo) {
    _create(pinPiezo);
}

void NGSoundMachine::_create(int pinPiezo) {
    _pinPiezo = pinPiezo;
}

void NGSoundMachine::initialize() {
    pinMode(_pinPiezo, OUTPUT);
}

void NGSoundMachine::play(NGCustomJingle *jingle) {
    play(jingle, jingle->getDefaultTempo());
}

void NGSoundMachine::play(NGCustomJingle *jingle, int tempo) {
    jingle->reset();
    while(jingle->hasTune()) {
        int tune = jingle->getTune();
        int beat = jingle->getBeat();
        if (tune == NO_NOTE) {
            noTone(_pinPiezo);
        } else {
            tone(_pinPiezo, tune, beat * tempo);
        }
        delay(beat * tempo);
        delay(tempo / 10);
    }
}
