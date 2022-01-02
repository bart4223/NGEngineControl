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

#include <NGCustomJingle.h>

#define DEFPINPIEZO 13
#define MAXJINGLES  10

class NGSoundMachine {
    
private:
    int _pinPiezo;
    NGCustomJingle *_jingles[MAXJINGLES];
    int _jingleCount = 0;
    
protected:
    void _create(int pinPiezo);
    
public:
    NGSoundMachine();
    
    NGSoundMachine(int pinPiezo);
    
    void initialize();
    
    int registerJingle(NGCustomJingle *jingle);
    
    void playRandom();
    
    void playRandom(int tempo);
    
    void play(byte jingle);
    
    void play(byte jingle, int tempo);
    
    int getJingleCount();
    
    int getMaxJingleCount();
    
    int getDefaultTempo(byte jingle);
};

#endif /* NGSoundMachine_h */
