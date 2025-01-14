//
//  NGJinglePopcorn.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.09.21.
//

#ifndef NGJinglePopcorn_h
#define NGJinglePopcorn_h

#include <Arduino.h>
#include <NGCustomJingle.h>

class NGJinglePopcorn : public NGCustomJingle {

private:
    int _tune[64] = {
        NOTE_C5, NOTE_AS4, NOTE_C5,  NOTE_G4,  NOTE_DS4, NOTE_G4,  NOTE_C4, NO_NOTE,
        NOTE_C5, NOTE_AS4, NOTE_C5,  NOTE_G4,  NOTE_DS4, NOTE_G4,  NOTE_C4, NO_NOTE,
        NOTE_C5, NOTE_D5,  NOTE_DS5, NOTE_D5,  NOTE_DS5, NOTE_C5,  NOTE_D5, NOTE_C5,
        NOTE_D5, NOTE_AS4, NOTE_C5,  NOTE_AS4, NOTE_C5,  NOTE_GS4, NOTE_C5, NO_NOTE,

        NOTE_C6, NOTE_AS5, NOTE_C6,  NOTE_G5,  NOTE_DS5, NOTE_G5,  NOTE_C5, NO_NOTE,
        NOTE_C6, NOTE_AS5, NOTE_C6,  NOTE_G5,  NOTE_DS5, NOTE_G5,  NOTE_C5, NO_NOTE,
        NOTE_C6, NOTE_D6,  NOTE_DS6, NOTE_D6,  NOTE_DS6, NOTE_C6,  NOTE_D6, NOTE_C6,
        NOTE_D6, NOTE_AS5, NOTE_C6,  NOTE_AS5, NOTE_C6,  NOTE_GS5, NOTE_C6, NO_NOTE
    };
    int _beat[64] = {
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1
    };
    
protected:
    void _create();
    
public:
    NGJinglePopcorn();
};

#endif /* NGJinglePopcorn_h */
