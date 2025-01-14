//
//  NGJingleBeep.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 19.12.21.
//

#ifndef NGJingleBeep_h
#define NGJingleBeep_h

#include <Arduino.h>
#include <NGCustomJingle.h>

class NGJingleBeep : public NGCustomJingle {

private:
    int _tune[1] = { NOTE_A6 };
    int _beat[1] = { 1 };
    
protected:
    void _create();
    
public:
    NGJingleBeep();
};

#endif /* NGJingleBeep_h */
