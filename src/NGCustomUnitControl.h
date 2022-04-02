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

#include <NGExceptionDefinitions.h>
#include <NGCustomNotification.h>
#include <NGRealTimeClock.h>

#define NOADDRESS           0x00
#define REQUESTEDDATALENGTH 6

// Command structure
//
// 1. Byte - Subject
//  2. Byte - Operation
// 0x00     None
//  0x00        Nop
// 0x01     Engine
//  0x00        Nop
//  0x01        RunForward
//  0x02        RunBackward
//  0x03        Stop
//  0x04        SetSpeed
// 0x02     Joint
//  0x00        Nop
//  0x01        Move
//  0x02        Simulate
//  0x03        MoveStepToMax
//  0x04        MoveStepToMin
//  0x05        Read
// 0x03     Gripper
//  0x00        Nop
//  0x01        Grip
//  0x02        Release
//   3. Byte - Name
//    max. 9 Bytes + 1 Byte 0xFF as Separator

#define OBSERVEMEMORYDELAY 5000

#define NOTIFICATIONCOUNT 3

#define CMDOffset           2
#define MaxCMDLength        15
#define CMDNameSeparator    0xFF

#define CMDSubject  0
#define CMDSNone    0x00
#define CMDSEngine  0x01
#define CMDSJoint   0x02
#define CMDSGripper 0x03

#define CMDOperation          1
#define CMDONop               0x00

#define CMDOEngineRunForward  0x01
#define CMDOEngineRunBackward 0x02
#define CMDOEngineStop        0x03
#define CMDOEngineSetSpeed    0x04

#define CMDOJointMove           0x01
#define CMDOJointSimulate       0x02
#define CMDOJointMoveStepToMax  0x03
#define CMDOJointMoveStepToMin  0x04
#define CMDOJointRead           0x05

#define CMDOGripperGrip       0x01
#define CMDOGripperRelease    0x02
#define CMDOGripperSimulate   0x03

enum workMode { wmNone, wmObserveMemory, wmCommand, wmSpec };

class NGCustomUnitControl {

protected:
    char* _name;
    char* _version;
    byte _address = NOADDRESS;
    bool _initialized;
    bool _logging;
    int _serialRate;
    NGCustomNotification *_notification[NOTIFICATIONCOUNT];
    int _notificationCount = 0;
    byte _receivedData[MaxCMDLength];
    int _receivedDataCount = 0;
    bool _receivingData = false;
    byte _requestedData[REQUESTEDDATALENGTH];
    workMode _workMode = wmNone;
    int _exceptionCount = 0;
    int _pinStartup = -1;
    NGRealTimeClock *_rtc = nullptr;

    void _create(char* name, byte address, int serialRate);
    
    void _clearState();
    
    void _writeState();
    
    void _writeTime();
    
    void _raiseException(int id);
    
    virtual void _processingReceivedData();
    
    virtual void _processingStartupLoop();

public:
    void initialize();
    
    long int startUp();
    
    void registerRealTimeClock(NGRealTimeClock *rtc);
    
    void registerNotification(NGCustomNotification *notification);
    
    void setWorkMode(workMode workmode);
    
    workMode getWorkMode();
    
    void registerStartup(int pinStartup);
    
    void processingLoop();
    
    void clearInfo();

    void writeInfo(char* info);

    void receiveDataStart();
    
    void receivedData(int index, byte data);
    
    void receiveDataFinish(int count);
    
    virtual void requestData(byte* data);
};

static NGCustomUnitControl *_globalUnit = NULL;

void setGlobalUnit(NGCustomUnitControl *unit);

bool hasGlobalUnit();

void globalUnitReceiveDataStart();

void globalUnitReceivedData(int index, byte data);

void globalUnitReceiveDataFinish(int count);

void globalUnitRequestData(byte* data);

#endif /* NGCustomUnitControl_h */
