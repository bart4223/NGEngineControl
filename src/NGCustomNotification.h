//
//  NGCustomNotification.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 11.06.21.
//

#ifndef NGCustomNotification_h
#define NGCustomNotification_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class NGCustomNotification {
       
public:
    virtual void initialize();
    virtual char* getName();
    virtual void clear();
    virtual void writeInfo(char* info);
    virtual void writeInfo(char* info, int line);
    virtual void writeInfo(char* info, int line, int column);

};
    
#endif /* NGCustomNotification_h */
