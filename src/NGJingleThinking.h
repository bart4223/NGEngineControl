//
//  NGJingleThinking.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 28.10.21.
//

#ifndef NGJingleThinking_h
#define NGJingleThinking_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomJingle.h>

class NGJingleThinking : public NGCustomJingle {

private:
    int _tune[8] = { NOTE_C4, NOTE_C4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_B3, NOTE_D4, NOTE_CS4 };
    int _beat[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
    
protected:
    void _create();
    
public:
    NGJingleThinking();
};

#endif /* NGJingleThinking_h */
