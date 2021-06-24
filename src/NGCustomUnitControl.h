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

// Command structure
//
// 1. Byte - Subject
//  2. Byte - Operation
// 0x00     None
//  0x00        Nop
// 0x01     Engine
//  0x00        Nop
// 0x02     Joint
//  0x00        Nop
// 0x03     Gripper
//  0x00        Nop
//  0x01        Grip
//  0x02        Release
//   3. Byte - Name
//    max. 9 Bytes + 1 Byte 0xFF as Separator

#define CMDOffset           2
#define MaxCMDLength        15
#define CMDNameSeparator    0xFF

#define CMDSubject  0
#define CMDSNone    0x00
#define CMDSEngine  0x01
#define CMDSJoint   0x02
#define CMDSGripper 0x03

#define CMDOperation       1
#define CMDONop            0x00
#define CMDOGripperGrip    0x01
#define CMDOGripperRelease 0x02

class NGCustomUnitControl {

protected:
    char* _name;
    byte _address = NOADDRESS;
    bool _initialized;
    bool _logging;
    int _serialRate;
    NGCustomNotification *_notification[3];
    int _notificationCount = 0;
    byte _receivedData[MaxCMDLength];
    int _receivedDataCount = 0;
    bool _receivingData = false;
    
    void _create(char* name, byte address, int serialRate);
    
    virtual void _processingReceivedData();

public:
    void initialize();
    
    void registerNotification(NGCustomNotification *notification);
    
    virtual void processingLoop();
    
    void clearInfo();

    void writeInfo(char* info);

    void writeInfo(char* info, int line);

    void writeInfo(char* info, int line, int column);
    
    void receiveDataStart();
    
    void receivedData(int index, byte data);
    
    void receiveDataFinish(int count);
    
    void requestData(byte* data);
};

static NGCustomUnitControl *_globalUnit = NULL;

void setGlobalUnit(NGCustomUnitControl *unit);

bool hasGlobalUnit();

void globalUnitReceiveDataStart();

void globalUnitReceivedData(int index, byte data);

void globalUnitReceiveDataFinish(int count);

void globalUnitRequestData(byte* data);

#endif /* NGCustomUnitControl_h */
