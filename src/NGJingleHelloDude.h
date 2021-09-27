//
//  NGJingleHelloDude.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 26.09.21.
//

#ifndef NGJingleHelloDude_h
#define NGJingleHelloDude_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomJingle.h>

class NGJingleHelloDude : public NGCustomJingle {

private:
    int _tune[6] = { NOTE_G5, NOTE_B5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_B5 };
    int _beat[6] = { 1, 1, 1, 1, 1, 3 };
    
protected:
    void _create();
    
public:
    NGJingleHelloDude();
};

#endif /* NGJingleHelloDude_h */
