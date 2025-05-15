//
//  NGCustomUnitControl.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.06.21.
//

#ifndef NGCustomUnitControl_h
#define NGCustomUnitControl_h

#include <Arduino.h>
#include <NGCommon.h>
#include <NGExceptionDefinitions.h>
#include <NGINotification.h>
#include <NGRealTimeClock.h>
#include <Misc/NGSimpleKeypad.h>
#include <NGSoundMachine.h>
#include <NGSplash.h>

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

#define NOSTARTUPPIN -1
#define NOSTARTUPLOOPS 0
#define NOJINGLE -1

#define NOTIFICATIONCOUNT   3

#define DEFSTARTUPLOOPSCOUNT    3

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

#ifdef NG_PLATFORM_MEGA
#define IRFUNCCOUNT      10
#else
#define IRFUNCCOUNT      3
#endif

#define DEFIRREMOTE 0x00

#define IRFUNCMENUDELAY 100

#define IRP_APPLE       0x14
#define IRP_APPLE_2     0x15
#define IRA_APPLE       0xA3
#define IRC_APPLE_MENU  0x02
#define IRC_APPLE_LEFT  0x08
#define IRC_APPLE_RIGHT 0x07
#define IRC_APPLE_UP    0x0B
#define IRC_APPLE_DOWN  0x0D
#define IRC_APPLE_OK    0x5D
#define IRC_APPLE_PLAY  0x5E

#define IRP_QIACHIP         0x42
#define IRA_QIACHIP         0x84
#define IRC_QIACHIP_LEFT    0x21
#define IRC_QIACHIP_RIGHT   0x22
#define IRC_QIACHIP_UP      0x23
#define IRC_QIACHIP_DOWN    0x24

void _unitWireReceiveEvent(int byteCount);

void _unitWireRequestEvent();

struct irremotefuncStruct
{
    byte remote;
    byte protocol;
    byte address;
    byte command;
    functionType type;
};
typedef struct irremotefuncStruct irremotefunc;

struct unitStruct
{
    char* name;
    byte address;
};
typedef struct unitStruct unit;

struct irremoteStruct
{
    byte remote;
    byte protocol;
    byte address;
    byte command;
};
typedef struct irremoteStruct irremote;

enum workMode { wmNone, wmObserveMemory, wmCommand, wmSpec };

class NGCustomUnitControl {

protected:
    char* _name;
    char* _version;
    byte _address = NOADDRESS;
    bool _initialized;
    bool _logging;
    int _serialRate;
    NGINotification *_notification[NOTIFICATIONCOUNT];
    int _notificationCount = 0;
    byte _receivedData[MaxCMDLength];
    int _receivedDataCount = 0;
    bool _receivingData = false;
    byte _requestedData[REQUESTEDDATALENGTH];
    workMode _workMode = wmNone;
    int _exceptionCount = 0;
    int _pinStartup = NOSTARTUPPIN;
    NGRealTimeClock *_rtc = nullptr;
    bool _rtcInitialize = false;
    bool _rtcAdjust = false;
    NGSimpleKeypad *_keypad = nullptr;
    NGSoundMachine *_soundMachine = nullptr;
    bool _createSoundMachine = true;
    int _jingleStartup = NOJINGLE;
    int _jingleStartupLoops = NOSTARTUPLOOPS;
    int _jingleBoot = NOJINGLE;
    int _jingleBeep = NOJINGLE;
    int _jingleAlarm = NOJINGLE;
    irremote _irremotedata;
    bool _irremotedataReceived = false;
    irremotefunc _irremotefunc[IRFUNCCOUNT];
    int _irremotefuncCount = 0;
    long _lastMemoryObserved = 0;
    NGSplash *_splash = nullptr;
    
    void _create(char* name, byte address, int serialRate);
    
    void _clearState();
    
    void _writeState();
    
    void _writeTime();
    
    void _raiseException(int id);
    
    virtual void _processingReceivedData();
    
    virtual void _processingStartupLoop();
    
    virtual void _processingIRRemoteData();

    int _registerJingle(NGCustomJingle *jingle);

    void _initializeSplash();
    
    void _initializeSoundMachine();

    void _initializeRTC();

    void _initializeKeypad();
    
    void _playJingle(byte jingle);
    
    void _playJingleStartup();
    
    void _playJingleBoot();
    
    void _playJingleBeep();
   
    void _playJingleAlarm();
    
    void _runSplash();

public:
    void initialize();
    
    char* getName();
    
    long int startUp();
    
    void registerRealTimeClock(NGRealTimeClock *rtc);

    void registerRealTimeClock(NGRealTimeClock *rtc, bool initialize);

    void registerRealTimeClock(NGRealTimeClock *rtc, bool initialize, bool adjust);
    
    void registerKeypad(NGSimpleKeypad *keypad);

    void registerNotification(NGINotification *notification);
    
    void setLogging(bool logging);
    
    bool getLogging();
    
    void setWorkMode(workMode workmode);
    
    workMode getWorkMode();
    
    void registerSplash(NGSplash *splash);
    
    void registerStartup(NGCustomJingle *jingle);
    
    void registerStartup(NGCustomJingle *jingle, int loops);

    void registerStartup(int pinStartup);
    
    void registerStartup(int pinStartup, NGCustomJingle *jingle);
    
    void registerStartup(int pinStartup, NGCustomJingle *jingle, int loops);

    void registerBoot(NGCustomJingle *jingle);
    
    void registerBeep(NGCustomJingle *jingle);
       
    void registerJingleAlarm(NGCustomJingle *jingle);
    
    void registerIRRemoteFunction(functionType type, byte protocol, byte address, byte command);

    void registerIRRemoteFunction(byte remote, functionType type, byte protocol, byte address, byte command);

    void processingLoop();
    
    void clearInfo();

    void writeInfo(char* info);

    void writeInfo(char* info, int threshold);

    void beep();
    
    void receiveDataStart();
    
    void receivedData(int index, byte data);
    
    void receiveDataFinish(int count);
    
    void setIRRemoteData(byte protocol, byte address, byte command);

    void setIRRemoteData(byte remote, byte protocol, byte address, byte command);
    
    virtual void requestData(byte* data);
};

static NGCustomUnitControl *_globalUnit = nullptr;

void setGlobalUnit(NGCustomUnitControl *unit);

bool hasGlobalUnit();

void globalUnitReceiveDataStart();

void globalUnitReceivedData(int index, byte data);

void globalUnitReceiveDataFinish(int count);

void globalUnitRequestData(byte* data);

#endif /* NGCustomUnitControl_h */
