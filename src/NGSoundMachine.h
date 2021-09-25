//
//  NGSoundMachine.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.09.21.
//

#ifndef NGSoundMachine_h
#define NGSoundMachine_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define DEFPINPIEZO 13

class NGSoundMachine {
    
private:
    int _pinPiezo;
    
protected:
    void _create(int pinPiezo);
    
public:
    NGSoundMachine();
    
    NGSoundMachine(int pinPiezo);
    
    void initialize();
    
    void play(NGCustomJingle *jingle);
    
    void play(NGCustomJingle *jingle, int tempo);
};

#endif /* NGSoundMachine_h */
