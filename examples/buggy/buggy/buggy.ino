#define PROD true //false,true

#include <NGMotionUnitControl.h>
#include <NGSerialNotification.h>
#include <NGJingleHelloDude.h>
#include <NGLightSensor.h>

#define _MOTION       "Motion"
#define MOTION        (char*)_MOTION
#define MOTIONADDRESS 0x21

#define PINSTARTUP  A1

NGMotionUnitControl unitMotion = NGMotionUnitControl(MOTION);
NGSerialNotification notificationSerial = NGSerialNotification();
NGJingleHelloDude jingleDude = NGJingleHelloDude();

void setup() {
  setGlobalUnit(&unitMotion);
  unitMotion.registerNotification(&notificationSerial);
  #if (PROD == true)
  unitMotion.registerStartup(PINSTARTUP, &jingleDude);
  #endif
  unitMotion.initialize();
  #if (PROD == false)
  unitMotion.setWorkMode(wmObserveMemory);
  #endif
  unitMotion.startUp();
  unitMotion.clearInfo();
}

void loop() {
  unitMotion.processingLoop();
}
