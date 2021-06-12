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
    int _address = 0;
    bool _initialized;
    bool _logging;
    int _serialRate;
    NGCustomNotification *_notification[3];
    int _notificationCount = 0;
    void _create(char* name, int address, int serialRate);
    void _clearInfo();
    void _writeInfo(char* info);
    void _writeInfo(char* info, int line);
    void _writeInfo(char* info, int line, int column);

public:
    void initialize();
    
    void registerNotification(NGCustomNotification *notification);
    
    virtual void processingLoop();
    
};

#endif /* NGCustomUnitControl_h */
