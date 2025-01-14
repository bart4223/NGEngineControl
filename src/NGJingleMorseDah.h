//
//  NGMorseDah.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 31.12.21.
//

#ifndef NGMorseDah_h
#define NGMorseDah_h

#include <Arduino.h>
#include <NGCustomJingle.h>

class NGJingleMorseDah : public NGCustomJingle {

private:
    int _tune[1] = { NOTE_E5 };
    int _beat[1] = { 3 };
    
protected:
    void _create();
    
public:
    NGJingleMorseDah();
};

#endif /* NGMorseDah_h */
