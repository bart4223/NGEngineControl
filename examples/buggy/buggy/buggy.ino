#define PROD true //false,true

#include <NGMotionUnitControl.h>
#include <NGSerialNotification.h>
#include <NGJingleHelloDude.h>
#include <NGLightSensor.h>

#define _MOTION       "Motion"
#define MOTION        (char*)_MOTION
#define MOTIONADDRESS 0x21

#define PINSTARTUP      A1
#define PINLIGHTSENSOR  A0
#define PINLIGHT         4

#define LIGHTSENSORDELAY      100
#define LIGHTSENSORTHRESHOLD  650

NGMotionUnitControl unitMotion = NGMotionUnitControl(MOTION);

void setup() {
  setGlobalUnit(&unitMotion);
  unitMotion.registerNotification(new NGSerialNotification());
  #if (PROD == true)
  unitMotion.registerStartup(PINSTARTUP, new NGJingleHelloDude());
  unitMotion.registerLightSensor(new NGLightSensor(PINLIGHTSENSOR), LIGHTSENSORTHRESHOLD, tlUnder, PINLIGHT, tvHigh, LIGHTSENSORDELAY);
  #else
  unitMotion.registerLightSensor(new NGLightSensor(PINLIGHTSENSOR), LIGHTSENSORTHRESHOLD, tlUnder, PINLIGHT, tvHigh);
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
