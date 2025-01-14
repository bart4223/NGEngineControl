//
//  NGJingleAlarm.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 26.09.21.
//

#ifndef NGJingleAlarm_h
#define NGJingleAlarm_h

#include <Arduino.h>
#include <NGCustomJingle.h>

class NGJingleAlarm : public NGCustomJingle {

private:
    int _tune[8] = { NOTE_D5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_E5 };
    int _beat[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
    
protected:
    void _create();
    
public:
    NGJingleAlarm();
};

#endif /* NGJingleAlarm_h */
