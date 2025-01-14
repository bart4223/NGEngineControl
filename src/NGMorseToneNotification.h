//
//  NGMorseToneNotification.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 16.01.22.
//

#ifndef NGMorseToneNotification_h
#define NGMorseToneNotification_h

#include <Arduino.h>
#include <NGINotification.h>
#include <NGCustomJingle.h>
#include <NGMorseToneGenerator.h>

#define DEFTEMPO 0

class NGMorseToneNotification : public NGINotification {

private:
    NGMorseToneGenerator *_morseToneGenerator;
    bool _playAllInfos = false;

protected:
    void _create(int pinPiezo, int tempo);
    
    void _playInfo(char *info);

public:
    NGMorseToneNotification();
    
    NGMorseToneNotification(int pinPiezo);
    
    NGMorseToneNotification(int pinPiezo, int tempo);
    
    void initialize();
    
    void registerJingleDit(NGCustomJingle *jingle);
    
    void registerJingleDah(NGCustomJingle *jingle);
    
    void registerJingleBreakLetter(NGCustomJingle *jingle);
    
    void registerJingleBreakWord(NGCustomJingle *jingle);
    
    char* getName();
    
    void clear();
    
    void clear(int line);
    
    void writeInfo(char* info);
    
    void writeInfo(char* info, int line);
    
    void writeInfo(char* info, int line, int column);
    
    void setPlayAllInfos(bool playAllInfos);
};

#endif /* NGMorseToneNotification_h */
