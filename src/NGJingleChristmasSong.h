//
//  NGJingleChristmasSong.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.12.21.
//

#ifndef NGJingleChristmasSong_h
#define NGJingleChristmasSong_h

#include <Arduino.h>
#include <NGCustomJingle.h>

class NGJingleChristmasSong : public NGCustomJingle {

private:

   int _tune[58] = {
        NOTE_GS6, NOTE_GS6, NOTE_GS6, NO_NOTE,
        NOTE_GS6, NOTE_GS6, NOTE_GS6, NO_NOTE,
        NOTE_GS6, NOTE_F6, NOTE_C7, NOTE_AS6,
        NOTE_GS6, NO_NOTE, NOTE_G6, NOTE_G6,
        NOTE_G6, NOTE_G6, NOTE_G6, NOTE_GS6,
        NOTE_GS6, NOTE_GS6, NOTE_GS6, NOTE_AS6,
        NOTE_AS6, NOTE_GS6, NOTE_AS6, NO_NOTE,
        NOTE_F6, NO_NOTE, NOTE_GS6, NOTE_GS6,
        NOTE_GS6, NO_NOTE, NOTE_GS6, NOTE_GS6,
        NOTE_GS6, NO_NOTE, NOTE_GS6, NOTE_F6,
        NOTE_C7, NOTE_AS6, NOTE_GS6, NO_NOTE,
        NOTE_G6, NOTE_G6, NOTE_G6, NOTE_G6,
        NOTE_G6, NOTE_GS6, NOTE_GS6, NOTE_GS6,
        NOTE_F6, NOTE_F6, NOTE_G6, NOTE_AS6,
        NOTE_C7, NO_NOTE
    };
    int _beat[58] = {
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1, 1, 1,
        1, 1
    };
    
protected:
    void _create();
    
public:
    NGJingleChristmasSong();
};

#endif /* NGJingleChristmasSong_h */
