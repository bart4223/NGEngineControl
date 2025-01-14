//
//  NGJingleBoot.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.11.21.
//

#ifndef NGJingleBoot_h
#define NGJingleBoot_h

#include <Arduino.h>
#include <NGCustomJingle.h>

class NGJingleBoot : public NGCustomJingle {

private:
    int _tune[3] = { NOTE_C3, NOTE_D3, NOTE_E3 };
    int _beat[3] = { 2, 4, 6 };
    
protected:
    void _create();
    
public:
    NGJingleBoot();
};

#endif /* NGJingleBoot_h */
