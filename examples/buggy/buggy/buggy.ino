#define PROD true //false,true

#include <NGMotionUnitControl.h>
#include <NGSerialNotification.h>
#include <NGJingleHelloDude.h>

#define _MOTION       "Motion"
#define MOTION        (char*)_MOTION
#define MOTIONADDRESS 0x21

#define PINSTARTUP A1

NGMotionUnitControl unitMotion = NGMotionUnitControl(MOTION);
NGSerialNotification notificationSerial = NGSerialNotification();

void setup() {
  setGlobalUnit(&unitMotion);
  #if (PROD == true)
  unitMotion.setStartup(PINSTARTUP);
  #endif
  unitMotion.registerNotification(&notificationSerial);
  #if (PROD == true)
  unitMotion.registerSplash(new NGJingleHelloDude);
  #endif
  unitMotion.initialize();
  #if (PROD == false)
  unitMotion.setWorkMode(wmObserveMemory);
  #endif
  unitMotion.clearInfo();
}

void loop() {
  unitMotion.processingLoop();
}
