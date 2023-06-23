#define PROD false //false,true

#include <NGBluetoothRemoteUnitControl.h>
#if (PROD == false)
#include <NGSerialNotification.h>
#endif

#define _REMOTE "Bluetooth Remote"
#define REMOTE  (char*)_REMOTE

#define _JOYSTICKRIGHT   "Joystick right"
#define JOYSTICKRIGHT    (char*)_JOYSTICKRIGHT

#define PINJOYSTICKRIGHTX     A0
#define PINJOYSTICKRIGHTY     A1
#define PINJOYSTICKRIGHTFIRE   7

#define THRESHOLDUP      512
#define THRESHOLDDOWN    511

#define DELAYRIGHTUP     50
#define DELAYRIGHTDOWN   50

NGBluetoothRemoteUnitControl unitRemote = NGBluetoothRemoteUnitControl(REMOTE);
#if (PROD == false)
NGSerialNotification serialNotification = NGSerialNotification();
#endif

void setup() {
  setGlobalUnit(&unitRemote);
  #if (PROD != true)
  unitRemote.registerNotification(&serialNotification);
  #else
  unitRemote.setLogging(false);
  #endif
  byte jsRight = unitRemote.registerJoystick(JOYSTICKRIGHT, PINJOYSTICKRIGHTX, PINJOYSTICKRIGHTY, PINJOYSTICKRIGHTFIRE);
  unitRemote.addJoystickAction(jsRight, jamMappingInvers, jaY, jtkLess, THRESHOLDUP, DELAYRIGHTUP, jmUp);
  unitRemote.addJoystickAction(jsRight, jamMapping, jaY, jtkGreater, THRESHOLDDOWN, DELAYRIGHTDOWN, jmDown);
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
