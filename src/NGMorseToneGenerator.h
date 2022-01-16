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

#define DEFPINPIEZO -1
#define DEFNOJINGLE -1

class NGMorseToneGenerator {

private:
    NGSoundMachine *_sm;
    int _jingleDit = DEFNOJINGLE;
    int _jingleDah = DEFNOJINGLE;
    int _jingleBreakLetter = DEFNOJINGLE;
    int _jingleBreakWord = DEFNOJINGLE;
    int _tempo = 0;

protected:
    void _create(int pinPiezo);
    
    void _playJingleDit();

    void _playJingleDah();

    void _playJingleBreakLetter();

    void _playJingleBreakWord();
    
    void _playLetter(byte letter);

public:
    NGMorseToneGenerator();
    
    NGMorseToneGenerator(int pinPiezo);
    
    void initialize();
    
    void registerJingleDit(NGCustomJingle *jingle);
    
    bool hasJingleDit();
    
    void registerJingleDah(NGCustomJingle *jingle);
    
    bool hasJingleDah();
    
    void registerJingleBreakLetter(NGCustomJingle *jingle);
    
    bool hasJingleBreakLetter();
    
    void registerJingleBreakWord(NGCustomJingle *jingle);
    
    bool hasJingleBreakWord();
    
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
    
    void playLetterAe();
    
    void playLetterOe();
    
    void playLetterUe();
    
    void playLetterSz();
    
    void playDigit1();
    
    void playDigit2();
    
    void playDigit3();
    
    void playDigit4();
    
    void playDigit5();
    
    void playDigit6();
    
    void playDigit7();
    
    void playDigit8();
    
    void playDigit9();
    
    void playDigit0();
    
    void playSignPoint();
    
    void playSignComma();
    
    void playSignDoublePoint();
    
    void playSignSemicolon();
    
    void playSignQuestionMark();
    
    void playSignExclamationMark();
    
    void playSignHyphen();
    
    void playSignUnderscore();
    
    void playSignBracketOpen();
    
    void playSignBracketClose();
    
    void playSignApostrophe();
    
    void playSignQuotationMarks();
    
    void playSignEqualSign();
    
    void playSignPlus();
    
    void playSignSlash();
    
    void playSignCommercialA();
    
    void playLetter(byte letter);
    
    void play(char* value);
    
    void playSOS();

    void playQAM();
    
    void playCQ(char* name);
};

#endif /* NGMorseToneGenerator_h */
