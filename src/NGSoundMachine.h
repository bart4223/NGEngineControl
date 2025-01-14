//
//  NGSoundMachine.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 25.09.21.
//

#ifndef NGSoundMachine_h
#define NGSoundMachine_h

#include <Arduino.h>
#include <NGCustomJingle.h>

#define DEFPINPIEZO 13
#define NOACTIVATIONPIN 0
#define MAXJINGLES  10

#define NOCURRENTJINGLE -1
#define NOCURRENTTUNE -1

class NGSoundMachine {
    
private:
    int _pinPiezo = DEFPINPIEZO; // needs PWM
    int _pinActivation = NOACTIVATIONPIN;
    NGCustomJingle *_jingles[MAXJINGLES];
    int _jingleCount = 0;
    bool _concurrently = false;
    int _currentJingle = NOCURRENTJINGLE;
    int _currentTempo;
    int _currentTune = NOCURRENTTUNE;
    int _currentBeat;
    int _currentDelay;
    long _lastTune = 0;
    
protected:
    void _create(int pinPiezo, int pinActivation);
    
public:
    NGSoundMachine();
    
    NGSoundMachine(int pinPiezo);
    
    NGSoundMachine(int pinPiezo, int pinActivation);
    
    void initialize();
    
    void activate();
    
    void deactivate();
    
    bool hasActivationPin();
    
    int registerJingle(NGCustomJingle *jingle);
    
    void playRandom();
    
    void playRandom(int tempo);
    
    void play(byte jingle);
    
    void play(byte jingle, int tempo);
    
    int getJingleCount();
    
    int getMaxJingleCount();
    
    int getDefaultTempo(byte jingle);
    
    void setConcurrently(bool concurrently);
    
    bool getConcurrently();
    
    bool hasCurrentJingle();
    
    void processingLoop();
};

#endif /* NGSoundMachine_h */
