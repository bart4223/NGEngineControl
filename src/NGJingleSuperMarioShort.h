//
//  NGJingleSuperMarioShort.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 26.09.21.
//

#ifndef NGJingleSuperMarioShort_h
#define NGJingleSuperMarioShort_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomJingle.h>

class NGJingleSuperMarioShort : public NGCustomJingle {

private:
    int _tune[9] = { NOTE_E7, NOTE_E7, NO_NOTE, NOTE_E7, NO_NOTE, NOTE_C7, NOTE_E7, NO_NOTE, NOTE_G7 };
    int _beat[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    
protected:
    void _create();
    
public:
    NGJingleSuperMarioShort();
};

#endif /* NGJingleSuperMarioShort_h */
