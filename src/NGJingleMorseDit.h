//
//  NGJingleMorseDit.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 31.12.21.
//

#ifndef NGJingleMorseDit_h
#define NGJingleMorseDit_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomJingle.h>

class NGJingleMorseDit : public NGCustomJingle {

private:
    int _tune[1] = { NOTE_FS5 };
    int _beat[1] = { 1 };
    
protected:
    void _create();
    
public:
    NGJingleMorseDit();
};

#endif /* NGJingleMorseDit_h */
