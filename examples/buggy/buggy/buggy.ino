#define PROD true //false,true

#include <NGMotionUnitControl.h>
#include <NGSerialNotification.h>
#include <NGLightSensor.h>
#include <NGFlashingLight.h>
#include <NGJingleHelloDude.h>

#define _MOTION       "Motion"
#define MOTION        (char*)_MOTION
#define MOTIONADDRESS 0x21

#define PINSTARTUP           A1
#define PINLIGHTSENSOR       A0
#define PINLIGHT              4
#define PINFLASHINGLIGHTLEFT  7
#define PINFLASHINGLIGHTRIGHT 8

#define LIGHTSENSORDELAY      400
#define LIGHTSENSORTHRESHOLD  650

#define FLASHINGLIGHTINTERVAL 250

NGMotionUnitControl unitMotion = NGMotionUnitControl(MOTION);
NGSerialNotification serialNotification = NGSerialNotification();
NGJingleHelloDude jingleHelloDude = NGJingleHelloDude();
NGLightSensor lightSensor = NGLightSensor(PINLIGHTSENSOR);
NGFlashingLight flLeft = NGFlashingLight(PINFLASHINGLIGHTLEFT, FLASHINGLIGHTINTERVAL);
NGFlashingLight flRight = NGFlashingLight(PINFLASHINGLIGHTRIGHT, FLASHINGLIGHTINTERVAL);

long int startUp;

void setup() {
  setGlobalUnit(&unitMotion);
  unitMotion.registerNotification(&serialNotification);
  #if (PROD == true)
  unitMotion.registerStartup(PINSTARTUP, &jingleHelloDude);
  unitMotion.registerLightSensor(&lightSensor, LIGHTSENSORTHRESHOLD, tlUnder, PINLIGHT, tvHigh, LIGHTSENSORDELAY);
  #else
  unitMotion.registerLightSensor(&lightSensor, LIGHTSENSORTHRESHOLD, tlUnder, PINLIGHT, tvHigh);
  #endif
  unitMotion.registerFlashingLights(&flLeft, &flRight);
  unitMotion.initialize();
  #if (PROD == false)
  unitMotion.setWorkMode(wmObserveMemory);
  #endif
  startUp = unitMotion.startUp();
  unitMotion.clearInfo();
}

void loop() {
  unitMotion.setWarningLight((millis() - startUp) < 15000);
  unitMotion.processingLoop();
}
