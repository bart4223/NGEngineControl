//
//  NGJingleMorseDit.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 31.12.21.
//

#ifndef NGJingleMorseDit_h
#define NGJingleMorseDit_h

#include <Arduino.h>
#include <NGCustomJingle.h>

class NGJingleMorseDit : public NGCustomJingle {

private:
    int _tune[1] = { NOTE_E5 };
    int _beat[1] = { 1 };
    
protected:
    void _create();
    
public:
    NGJingleMorseDit();
};

#endif /* NGJingleMorseDit_h */
