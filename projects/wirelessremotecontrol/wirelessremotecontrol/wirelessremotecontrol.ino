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
#define OLEDTYPE          ot128x64
#define OLEDLINES         8
#define OLEDLINEFACTOR    4

#define PINJOYSTICKRIGHTX     A0
#define PINJOYSTICKRIGHTY     A1
#define PINJOYSTICKRIGHTFIRE   7
#define PINJOYSTICKRIGHTUP    11
#define PINJOYSTICKRIGHTDOWN  10
#define PINJOYSTICKRIGHTLEFT   9
#define PINJOYSTICKRIGHTRIGHT  8

#define PINJOYSTICKLEFTX     A2
#define PINJOYSTICKLEFTY     A3
#define PINJOYSTICKLEFTFIRE   2
#define PINJOYSTICKLEFTUP     6
#define PINJOYSTICKLEFTDOWN   5
#define PINJOYSTICKLEFTLEFT   4
#define PINJOYSTICKLEFTRIGHT  3

#define THRESHOLDUP       400
#define THRESHOLDDOWN     623
#define THRESHOLDLEFT     400
#define THRESHOLDRIGHT    623

#define DELAY 200
#define TRIGGERDELAY 20

#define DELAYRIGHTUP     500
#define DELAYRIGHTDOWN   500
#define DELAYRIGHTLEFT   100
#define DELAYRIGHTRIGHT  100

NGWirelessRemoteUnitControl unitRemote = NGWirelessRemoteUnitControl(REMOTE);
#if (PROD == false)
NGSerialNotification serialNotification = NGSerialNotification();
#endif
NGOLEDNotification *oledNotification;

void setup() {
  setGlobalUnit(&unitRemote);
  #if (PROD != true)
  unitRemote.registerNotification(&serialNotification);
  #else
  unitRemote.setLogging(false);
  #endif
  oledNotification = new NGOLEDNotification(OLEDTYPE, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  unitRemote.registerNotification(oledNotification);
  byte jsleft = unitRemote.registerJoystick(JOYSTICKLEFT, PINJOYSTICKLEFTX, PINJOYSTICKLEFTY, PINJOYSTICKLEFTFIRE);
  unitRemote.addJoystickAction(jsleft, PINJOYSTICKLEFTLEFT, jamTriggerLOW, jaX, jtkGreater, THRESHOLDRIGHT, DELAY, jmLeft);
  unitRemote.addJoystickAction(jsleft, PINJOYSTICKLEFTRIGHT, jamTriggerLOW, jaX, jtkLess, THRESHOLDLEFT, DELAY, jmRight);
  unitRemote.addJoystickAction(jsleft, PINJOYSTICKLEFTUP, jamTriggerLOW, jaY, jtkGreater, THRESHOLDDOWN, DELAY, jmUp);
  unitRemote.addJoystickAction(jsleft, PINJOYSTICKLEFTDOWN, jamTriggerLOW, jaY, jtkLess, THRESHOLDUP, DELAY, jmDown);
  byte jsRight = unitRemote.registerJoystick(JOYSTICKRIGHT, PINJOYSTICKRIGHTX, PINJOYSTICKRIGHTY, PINJOYSTICKRIGHTFIRE);
  unitRemote.addJoystickAction(jsRight, PINJOYSTICKRIGHTLEFT, jamTriggerLOW, jaX, jtkLess, THRESHOLDLEFT, DELAYRIGHTLEFT, jmLeft, TRIGGERDELAY);
  unitRemote.addJoystickAction(jsRight, PINJOYSTICKRIGHTRIGHT, jamTriggerLOW, jaX, jtkGreater, THRESHOLDRIGHT, DELAYRIGHTRIGHT, jmRight, TRIGGERDELAY);
  unitRemote.addJoystickAction(jsRight, PINJOYSTICKRIGHTUP, jamTriggerLOW, jaY, jtkLess, THRESHOLDUP, DELAYRIGHTUP, jmUp, TRIGGERDELAY);
  unitRemote.addJoystickAction(jsRight, PINJOYSTICKRIGHTDOWN, jamTriggerLOW, jaY, jtkGreater, THRESHOLDDOWN, DELAYRIGHTDOWN, jmDown, TRIGGERDELAY);
  unitRemote.initialize();
  #if (PROD == true)
  unitRemote.setWorkMode(wmNone);
  #else
  //unitRemote.setWorkMode(wmObserveMemory);
  #endif
  unitRemote.startUp();
  unitRemote.clearInfo();
}

void loop() {
  unitRemote.processingLoop();
}
