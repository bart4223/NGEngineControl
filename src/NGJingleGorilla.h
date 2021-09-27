//
//  NGJingleGorilla.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.09.21.
//

#ifndef NGJingleGorilla_h
#define NGJingleGorilla_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomJingle.h>

class NGJingleGorilla : public NGCustomJingle {

private:
    int _tune[12] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_C4, NO_NOTE, NO_NOTE, NO_NOTE};
    int _beat[12] = { 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1};
    
protected:
    void _create();
    
public:
    NGJingleGorilla();
    
    int getDefaultTempo();
};

#endif /* NGJingleGorilla_h */
