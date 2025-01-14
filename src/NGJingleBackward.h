//
//  NGJingleBackward.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 18.10.21.
//

#ifndef NGJingleBackward_h
#define NGJingleBackward_h

#include <Arduino.h>
#include <NGCustomJingle.h>

class NGJingleBackward : public NGCustomJingle {

private:
    int _tune[2] = { NOTE_B5, NO_NOTE };
    int _beat[2] = { 4, 2 };
    
protected:
    void _create();
    
public:
    NGJingleBackward();
};

#endif /* NGJingleBackward_h */
