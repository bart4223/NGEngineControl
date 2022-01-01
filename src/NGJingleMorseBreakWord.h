//
//  NGJingleMorseBreakWord.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 01.01.22.
//

#ifndef NGJingleMorseBreakWord_h
#define NGJingleMorseBreakWord_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomJingle.h>

class NGJingleMorseBreakWord : public NGCustomJingle {

private:
    int _tune[1] = { NO_NOTE };
    int _beat[1] = { 7 };
    
protected:
    void _create();
    
public:
    NGJingleMorseBreakWord();
};

#endif /* NGJingleMorseBreakWord_h */
