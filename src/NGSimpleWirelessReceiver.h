//
//  NGSimpleWirelessReceiver.h
//  NGEngineControl
//
//  Created by Nils Grimmer on 09.08.22.
//

#ifndef NGSimpleWirelessReceiver_h
#define NGSimpleWirelessReceiver_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define MAXSWRCALLBACKOUNT         4
#define SWRNODELAY                 0
#define SWRNOCURRENTCALLBACK      -1
#define SWRNOPROTOCOL           0x00
#define DEFREMOTEID             0x00

// Chip QIACHIP wireless RX480E-4WQB 433Mhz
//
// 1. Delete existing data
//    Press the learn button (on the receiver) 8 times. Response: LED flashes 7 times.
// 2. Learning the remote code
//    Press the learning button (on the receiver) once, twice or three times. LED lights up: Learning mode is active. Press any button on the remote control.
//    LED indicator flashes three times: Learning completed successfully.
// 3. Test
//    After the above process, the receiver board can be controlled with the remote control. From step 2, additional transmitters with different IDs can be learned and saved.
//    A mixture of different modes is possible.
// Button operation (set mode and start pairing)
//    Press once: Inching mode (Momentary mode) ) Press twice: Self-lock mode (Toggle mode of the 4 channels) Press three times: Interlock mode
//    (selected channel active and will be cleared when another channel becomes active)

typedef void (*simpleWirelessReceiverCallbackFunc)();

enum simpleWirelessReceiverMode { swrmLOW, swrmHIGH };

struct simpleWirelessReceiverCallbackStruct
{
    int pin;
    int delay;
    long int lastFire = 0;
    simpleWirelessReceiverMode mode;
    simpleWirelessReceiverCallbackFunc callback;
    byte protocol = 0x00;
    byte address = 0x00;
    byte command = 0x00;
};
typedef struct simpleWirelessReceiverCallbackStruct simpleWirelessReceiverCallback;

class NGSimpleWirelessReceiver {
  
private:
    simpleWirelessReceiverCallback _receiverCallbacks[MAXSWRCALLBACKOUNT];
    int _receiverCallbackCount = 0;
    int _currentCallback = SWRNOCURRENTCALLBACK;
    byte _ID = DEFREMOTEID;
    
protected:
    void _create(byte ID);
    
    void _resetCurrentCallback();
    
public:
    NGSimpleWirelessReceiver();
       
    NGSimpleWirelessReceiver(byte ID);
    
    void registerCallback(int pin, simpleWirelessReceiverCallbackFunc callback);
    
    void registerCallback(int pin, simpleWirelessReceiverMode mode, simpleWirelessReceiverCallbackFunc callback);
    
    void registerCallback(int pin, simpleWirelessReceiverCallbackFunc callback, int delay);
    
    void registerCallback(int pin, simpleWirelessReceiverMode mode, simpleWirelessReceiverCallbackFunc callback, int delay);
    
    void registerCommand(int pin, byte protocol, byte address, byte command);
    
    void registerCommand(int pin, byte protocol, byte address, byte command, int delay);
    
    void registerCommand(int pin, simpleWirelessReceiverMode mode, byte protocol, byte address, byte command, int delay);
    
    void initialize();
    
    void processingLoop();
    
    bool isCommandReceived();
    
    byte getReceivedCommandProtocol();

    byte getReceivedCommandAddress();

    byte getReceivedCommand();
    
    byte getID();
};

#endif /* NGSimpleWirelessReceiver_h */
