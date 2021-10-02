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
NGSerialNotification serialNotification = NGSerialNotification();
NGJingleHelloDude jingleHelloDude = NGJingleHelloDude();
NGLightSensor lightSensor = NGLightSensor(PINLIGHTSENSOR);

void setup() {
  setGlobalUnit(&unitMotion);
  unitMotion.registerNotification(&serialNotification);
  #if (PROD == true)
  unitMotion.registerStartup(PINSTARTUP, &jingleHelloDude);
  unitMotion.registerLightSensor(&lightSensor, LIGHTSENSORTHRESHOLD, tlUnder, PINLIGHT, tvHigh, LIGHTSENSORDELAY);
  #else
  unitMotion.registerLightSensor(&lightSensor, LIGHTSENSORTHRESHOLD, tlUnder, PINLIGHT, tvHigh);
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
