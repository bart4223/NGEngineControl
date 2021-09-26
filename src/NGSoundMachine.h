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
#define MAXJINGLES   5

class NGSoundMachine {
    
private:
    int _pinPiezo;
    NGCustomJingle *_jingles[MAXJINGLES];
    int _jingleCount;
    
protected:
    void _create(int pinPiezo);
    
public:
    NGSoundMachine();
    
    NGSoundMachine(int pinPiezo);
    
    void initialize();
    
    byte registerJingle(NGCustomJingle *jingle);
    
    void playRandom();
    
    void play(byte jingle);
    
    void play(byte jingle, int tempo);
};

#endif /* NGSoundMachine_h */
