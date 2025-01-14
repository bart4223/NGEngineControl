//
//  NGJingleMorseBreakWord.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 01.01.22.
//

#ifndef NGJingleMorseBreakWord_h
#define NGJingleMorseBreakWord_h

#include <Arduino.h>
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
