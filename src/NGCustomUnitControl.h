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

class NGCustomUnitControl {

protected:
    char* _name;
    bool _initialized;
    bool _logging;
    int _serialRate;
    NGCustomNotification *_notification = NULL;
    void _create(char* name, int serialRate);
    void _writeInfo(char* info);

public:
    void initialize();
    void registerNotification(NGCustomNotification *notification);

};

#endif /* NGCustomUnitControl_h */