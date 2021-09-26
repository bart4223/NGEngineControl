//
//  NGJingleSuperMario.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.09.21.
//

#ifndef NGJingleSuperMario_h
#define NGJingleSuperMario_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomJingle.h>

class NGJingleSuperMario : public NGCustomJingle {

private:
    int _tune[90] = {
        NOTE_E7, NOTE_E7, NO_NOTE, NOTE_E7, NO_NOTE, NOTE_C7, NOTE_E7, NO_NOTE,
        NOTE_G7, NO_NOTE, NO_NOTE, NO_NOTE, NOTE_G6, NO_NOTE, NO_NOTE, NO_NOTE,
        NOTE_C7, NO_NOTE, NO_NOTE, NOTE_G6, NO_NOTE, NO_NOTE, NOTE_E6, NO_NOTE,
        NO_NOTE, NOTE_A6, NO_NOTE, NOTE_B6, NO_NOTE, NOTE_AS6, NOTE_A6, NO_NOTE,
     
        NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, NO_NOTE, NOTE_F7, NOTE_G7, NO_NOTE,
        NOTE_E7, NO_NOTE, NOTE_C7, NOTE_D7, NOTE_B6, NO_NOTE, NO_NOTE,
        NOTE_C7, NO_NOTE, NO_NOTE, NOTE_G6, NO_NOTE, NO_NOTE, NOTE_E6, NO_NOTE,
        NO_NOTE, NOTE_A6, NO_NOTE, NOTE_B6, NO_NOTE, NOTE_AS6, NOTE_A6, NO_NOTE,
     
        NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, NO_NOTE, NOTE_F7, NOTE_G7,
        NO_NOTE, NOTE_E7, NO_NOTE, NOTE_C7, NOTE_D7, NOTE_B6, NO_NOTE, NO_NOTE
    };
    int _beat[90] = {
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
     
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
     
        1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
     
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
     
        1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
    };
    
protected:
    void _create();
    
public:
    NGJingleSuperMario();
    
    int getDefaultTempo();
    
    int getTune();
    
    int getBeat();
};

#endif /* NGJingleSuperMario_h */
