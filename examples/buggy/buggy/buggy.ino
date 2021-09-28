#define PROD false //false,true

#include <NGMotionUnitControl.h>
#include <NGSerialNotification.h>

#define _MOTION       "Motion"
#define MOTION        (char*)_MOTION
#define MOTIONADDRESS 0x21

#define STARTUP A1

NGMotionUnitControl unitMotion = NGMotionUnitControl(MOTION);
NGSerialNotification notificationSerial = NGSerialNotification();

void setup() {
  setGlobalUnit(&unitMotion);
  unitMotion.setStartup(STARTUP);
  unitMotion.registerNotification(&notificationSerial);
  unitMotion.initialize();
  #if (PROD == false)
  unitMotion.setWorkMode(wmObserveMemory);
  #endif
  unitMotion.clearInfo();
}

void loop() {
  unitMotion.processingLoop();
}
