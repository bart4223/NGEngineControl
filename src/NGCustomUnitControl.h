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

#define NOADDRESS 0x00

class NGCustomUnitControl {

protected:
    char* _name;
    byte _address = 0x00;
    bool _initialized;
    bool _logging;
    int _serialRate;
    NGCustomNotification *_notification[3];
    int _notificationCount = 0;
    byte _receivedData[10];
    int _receivedDataCount = 0;
    bool _receivingData = false;
    void _create(char* name, byte address, int serialRate);
    void _processingReceivedData();

public:
    void initialize();
    
    void registerNotification(NGCustomNotification *notification);
    
    void processingLoop();
    
    void clearInfo();

    void writeInfo(char* info);

    void writeInfo(char* info, int line);

    void writeInfo(char* info, int line, int column);
    
    void receiveDataStart();
    
    void receivedData(int index, byte data);
    
    void receiveDataFinish(int count);
};

static NGCustomUnitControl *_unit = NULL;

#endif /* NGCustomUnitControl_h */
