#define PROD true //false,true

#include <NGWirelessRemoteUnitControl.h>
#if (PROD == false)
#include <NGSerialNotification.h>
#endif
#include <NGOLEDNotification.h>

#define _REMOTE           "Wireless Remote"
#define REMOTE            (char*)_REMOTE
#define REMOTEADDRESS     0x24

#define _JOYSTICKLEFT    "Joystick left"
#define JOYSTICKLEFT     (char*)_JOYSTICKLEFT
#define _JOYSTICKRIGHT   "Joystick right"
#define JOYSTICKRIGHT    (char*)_JOYSTICKRIGHT

#define OLEDADDRESS       0x3C
#define OLEDCOLUMNS       16
#define OLEDTYPE          ot128x32
#define OLEDLINES         4
#define OLEDLINEFACTOR    2

#define PINUP     3
#define PINDOWN   4
#define PINLEFT   5
#define PINRIGHT  6

#define THRESHOLDUP       100
#define THRESHOLDDOWN     923
#define THRESHOLDLEFT     100
#define THRESHOLDRIGHT    923

#define DELAY 200

NGWirelessRemoteUnitControl unitRemote = NGWirelessRemoteUnitControl(REMOTE);
#if (PROD == false)
NGSerialNotification serialNotification = NGSerialNotification();
#endif
NGOLEDNotification *oledNotification;

void setup() {
  setGlobalUnit(&unitRemote);
  #if (PROD != true)
  unitRemote.registerNotification(&serialNotification);
  #endif
  oledNotification = new NGOLEDNotification(OLEDTYPE, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  unitRemote.registerNotification(oledNotification);
  byte jsleft = unitRemote.registerJoystick(JOYSTICKLEFT);
  byte jsRight = unitRemote.registerJoystick(JOYSTICKRIGHT);
  unitRemote.addJoystickAction(jsRight, PINLEFT, jamTriggerLOW, jaX, jtkLess, THRESHOLDLEFT, DELAY);
  unitRemote.addJoystickAction(jsRight, PINRIGHT, jamTriggerLOW, jaX, jtkGreater, THRESHOLDRIGHT, DELAY);
  unitRemote.addJoystickAction(jsRight, PINUP, jamTriggerLOW, jaY, jtkLess, THRESHOLDUP, DELAY);
  unitRemote.addJoystickAction(jsRight, PINDOWN, jamTriggerLOW, jaY, jtkGreater, THRESHOLDDOWN, DELAY);
  unitRemote.initialize();
  #if (PROD == true)
  unitRemote.setWorkMode(wmNone);
  #else
  unitRemote.setWorkMode(wmObserveMemory);
  #endif
  unitRemote.startUp();
  unitRemote.clearInfo();
}

void loop() {
  unitRemote.processingLoop();
}
