//
//  NGJingleMorseBreakLetter.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 01.01.22.
//

#ifndef NGJingleMorseBreakLetter_h
#define NGJingleMorseBreakLetter_h

#include <Arduino.h>
#include <NGCustomJingle.h>

class NGJingleMorseBreakLetter : public NGCustomJingle {

private:
    int _tune[1] = { NO_NOTE };
    int _beat[1] = { 3 };
    
protected:
    void _create();
    
public:
    NGJingleMorseBreakLetter();
};

#endif /* NGJingleMorseBreakLetter_h */
