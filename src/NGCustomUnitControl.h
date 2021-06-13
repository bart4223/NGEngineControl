//
//  NGCustomUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.06.21.
//

#ifndef NGCustomUnitControl_h
#define NGCustomUnitControl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <NGCustomNotification.h>

#define NOADDRESS 0

class NGCustomUnitControl {

protected:
    char* _name;
    byte _address = 0x00;
    bool _initialized;
    bool _logging;
    int _serialRate;
    NGCustomNotification *_notification[3];
    int _notificationCount = 0;
    void _create(char* name, byte address, int serialRate);

public:
    void initialize();
    
    void registerNotification(NGCustomNotification *notification);
    
    virtual void processingLoop();

    void clearInfo();

    void writeInfo(char* info);

    void writeInfo(char* info, int line);

    void writeInfo(char* info, int line, int column);
    
};

static NGCustomUnitControl *_unit = NULL;

#endif /* NGCustomUnitControl_h */
