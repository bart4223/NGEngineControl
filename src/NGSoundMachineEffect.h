//
//  NGSoundMachineEffect.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 31.08.24.
//

#ifndef NGSoundMachineEffect_h
#define NGSoundMachineEffect_h

#include <Arduino.h>
#include <NGIEffect.h>
#include <NGSoundMachine.h>

#define NOJINGLE -1

class NGSoundMachineEffect: public NGIEffect {
    
private:
    NGSoundMachine *_soundMachine;
    int _jingle = NOJINGLE;
    
protected:
    void _create(NGSoundMachine *soundmachine);
    
public:
    NGSoundMachineEffect(NGSoundMachine *soundmachine);
    
    void initialize();
    
    void playJingle(byte jingle);
    
    void processingLoop();
};

#endif /* NGSoundMachineEffect_h */
