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

#define PINJOYSTICKRIGHTX     A0
#define PINJOYSTICKRIGHTY     A1
#define PINJOYSTICKRIGHTFIRE   2
#define PINJOYSTICKRIGHTUP     3
#define PINJOYSTICKRIGHTDOWN   4
#define PINJOYSTICKRIGHTLEFT   5
#define PINJOYSTICKRIGHTRIGHT  6

#define PINJOYSTICKLEFTX     A2
#define PINJOYSTICKLEFTY     A3
#define PINJOYSTICKLEFTFIRE   7
#define PINJOYSTICKLEFTUP     8
#define PINJOYSTICKLEFTDOWN   9
#define PINJOYSTICKLEFTLEFT   10
#define PINJOYSTICKLEFTRIGHT  11

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
  byte jsleft = unitRemote.registerJoystick(JOYSTICKLEFT, PINJOYSTICKLEFTX, PINJOYSTICKLEFTY, PINJOYSTICKLEFTFIRE);
  unitRemote.addJoystickAction(jsleft, PINJOYSTICKLEFTLEFT, jamTriggerLOW, jaX, jtkLess, THRESHOLDLEFT, DELAY);
  unitRemote.addJoystickAction(jsleft, PINJOYSTICKLEFTRIGHT, jamTriggerLOW, jaX, jtkGreater, THRESHOLDRIGHT, DELAY);
  unitRemote.addJoystickAction(jsleft, PINJOYSTICKLEFTUP, jamTriggerLOW, jaY, jtkLess, THRESHOLDUP, DELAY);
  unitRemote.addJoystickAction(jsleft, PINJOYSTICKLEFTDOWN, jamTriggerLOW, jaY, jtkGreater, THRESHOLDDOWN, DELAY);
  byte jsRight = unitRemote.registerJoystick(JOYSTICKRIGHT, PINJOYSTICKRIGHTX, PINJOYSTICKRIGHTY, PINJOYSTICKRIGHTFIRE);
  unitRemote.addJoystickAction(jsRight, PINJOYSTICKRIGHTLEFT, jamTriggerLOW, jaX, jtkLess, THRESHOLDLEFT, DELAY);
  unitRemote.addJoystickAction(jsRight, PINJOYSTICKRIGHTRIGHT, jamTriggerLOW, jaX, jtkGreater, THRESHOLDRIGHT, DELAY);
  unitRemote.addJoystickAction(jsRight, PINJOYSTICKRIGHTUP, jamTriggerLOW, jaY, jtkLess, THRESHOLDUP, DELAY);
  unitRemote.addJoystickAction(jsRight, PINJOYSTICKRIGHTDOWN, jamTriggerLOW, jaY, jtkGreater, THRESHOLDDOWN, DELAY);
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
