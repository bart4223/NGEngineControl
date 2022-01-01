//
//  NGMorseToneGenerator.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 01.01.22.
//

#ifndef NGMorseToneGenerator_h
#define NGMorseToneGenerator_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "NGSoundMachine.h"

class NGMorseToneGenerator {

private:
    NGSoundMachine *_sm;
    int _jingleDit = -1;
    int _jingleDah = -1;
    int _jingleBreakLetter = -1;
    int _jingleBreakWord = -1;
    int _tempo = 0;

protected:
    void _create();
    
    void _playJingleDit();

    void _playJingleDah();

    void _playJingleBreakLetter();

    void _playJingleBreakWord();

public:
    NGMorseToneGenerator();
    
    void initialize();
    
    void registerJingleDit(NGCustomJingle *jingle);
    
    void registerJingleDah(NGCustomJingle *jingle);
    
    void registerJingleBreakLetter(NGCustomJingle *jingle);
    
    void registerJingleBreakWord(NGCustomJingle *jingle);
    
    void setTempo(int tempo);
    
    void playLetterA();

    void playLetterB();

    void playLetterC();

    void playLetterD();

    void playLetterE();

    void playLetterF();

    void playLetterG();

    void playLetterH();

    void playLetterI();

    void playLetterJ();

    void playLetterK();

    void playLetterL();

    void playLetterM();

    void playLetterN();

    void playLetterO();

    void playLetterP();

    void playLetterQ();

    void playLetterR();

    void playLetterS();

    void playLetterT();

    void playLetterU();

    void playLetterV();

    void playLetterW();

    void playLetterX();

    void playLetterY();
    
    void playLetterZ();
    
    void playLetter(char letter);
    
    void play(char* value);
    
    void playSOS();
};

#endif /* NGMorseToneGenerator_h */
