#define PROD false //false,true

#include <NGAnchormanUnitControl.h>
#include <NGSimpleKeypad.h>
#if (PROD == false)
#include <NGSerialNotification.h>
#endif
#include <NGOLEDNotification.h>
#include <NGJingleBoot.h>
#include <NGJingleBeep.h>

#define _ANCHORMNAN "Anchorman"
#define ANCHORMNAN  (char*)_ANCHORMNAN

#define OLEDADDRESS       0x3C
#define OLEDCOLUMNS       16
#define OLEDTYPE          ot128x32
#define OLEDLINES         4
#define OLEDLINEFACTOR    2

#define TURNTABLESPEED         128
#define TURNTABLEDELAY         125
#define MOTIONPROFILERUNFORWARD    250
#define MOTIONPROFILERUNBACKWARD   250
#define MOTIONPROFILESTOP        60000

#define KEYMODEPIN    2
#define KEYUPPIN      3
#define KEYDOWNPIN    4
#define KEYMODEID    10
#define KEYMODEUP    11
#define KEYMODEDOWN  12
#define KEYPADDELAY 500

NGAnchormanUnitControl unitAnchorman = NGAnchormanUnitControl(ANCHORMNAN);
NGSimpleKeypad keypad = NGSimpleKeypad();
#if (PROD == false)
NGSerialNotification serialNotification = NGSerialNotification();
#endif
NGOLEDNotification *oledNotification;

void setup() {
  setGlobalUnit(&unitAnchorman);
  #if (PROD != true)
  unitAnchorman.registerNotification(&serialNotification);
  #else
  unitAnchorman.setLogging(false);
  #endif
  oledNotification = new NGOLEDNotification(OLEDTYPE, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  unitAnchorman.registerNotification(oledNotification);
  unitAnchorman.registerBoot(new NGJingleBoot);
  unitAnchorman.registerBeep(new NGJingleBeep);
  int ttmp = unitAnchorman.registerSimpleTurnTableMotionProfile(MOTIONPROFILERUNFORWARD, MOTIONPROFILESTOP, MOTIONPROFILERUNBACKWARD, MOTIONPROFILESTOP);
  unitAnchorman.registerTurnTable(new NGEngineControl(ENGINE_2), TURNTABLESPEED, TURNTABLEDELAY, ttmp);
  unitAnchorman.initialize();
  keypad.registerCallback(&KeypadCallback);
  keypad.registerKey(KEYMODEPIN, KEYMODEID, KEYPADDELAY);
  keypad.registerKey(KEYUPPIN, KEYMODEUP, KEYPADDELAY);
  keypad.registerKey(KEYDOWNPIN, KEYMODEDOWN, KEYPADDELAY);
  keypad.initialize();
  #if (PROD == true)
  unitAnchorman.setWorkMode(wmNone);
  #else
  unitAnchorman.setWorkMode(wmObserveMemory);
  #endif
  unitAnchorman.startUp();
  unitAnchorman.clearInfo();
}

void loop() {
  keypad.processingLoop();
  unitAnchorman.processingLoop();
}

void KeypadCallback(byte id) {
  char log[100];
  sprintf(log, "Call -> %d", id);
  unitAnchorman.clearInfo();
  unitAnchorman.writeInfo(log);
}
