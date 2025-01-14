//
//  NGJingleJingleBells.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.12.21.
//

#ifndef NGJingleJingleBells_h
#define NGJingleJingleBells_h

#include <Arduino.h>
#include <NGCustomJingle.h>

class NGJingleJingleBells : public NGCustomJingle {

private:

    int _tune[26] = {
        NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
        NOTE_E4, NOTE_E4, NOTE_E4, NOTE_G4,
        NOTE_C4, NOTE_D4, NOTE_E4, NO_NOTE,
        NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4,
        NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4,
        NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4,
        NOTE_D4, NOTE_G4
    };
    int _beat[26] = {
        1, 1, 2, 1,
        1, 2, 1, 1,
        1, 1, 2, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        2, 2
    };
    
protected:
    void _create();
    
public:
    NGJingleJingleBells();
};

#endif /* NGJingleJingleBells_h */
