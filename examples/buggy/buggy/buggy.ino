#define PROD              true  //false,true
#define ScenarioStartStop true  //false,true
#define ScenarioTurnLeft  false //false,true

#include <NGMotionUnitControl.h>
#include <NGSerialNotification.h>
#include <NGLightSensor.h>
#include <NGFlashingLight.h>
#include <NGJingleHelloDude.h>

#define _MOTION       "Motion"
#define MOTION        (char*)_MOTION
#define MOTIONADDRESS 0x21

#define ENGINEOFFSETLEFT    15
#define ENGINEOFFSETRIGHT  -15

#define PINLIGHTSENSOR       A0
#define PINSTARTUP           A1
#define PINBRAKELIGHT         2
#define PINLIGHT              4
#define PINFLASHINGLIGHTLEFT  7
#define PINFLASHINGLIGHTRIGHT 8

#define LIGHTSENSORDELAY      500
#define LIGHTSENSORTHRESHOLD  650

#define FLASHINGLIGHTINTERVAL 250

#define SPEEDEASY   200
#define SPEEDCURVE  100

NGMotionUnitControl unitMotion = NGMotionUnitControl(MOTION, ENGINEOFFSETLEFT, ENGINEOFFSETRIGHT);
NGSerialNotification serialNotification = NGSerialNotification();
NGJingleHelloDude jingleHelloDude = NGJingleHelloDude();
NGLightSensor lightSensor = NGLightSensor(PINLIGHTSENSOR);
NGFlashingLight flLeft = NGFlashingLight(PINFLASHINGLIGHTLEFT, FLASHINGLIGHTINTERVAL);
NGFlashingLight flRight = NGFlashingLight(PINFLASHINGLIGHTRIGHT, FLASHINGLIGHTINTERVAL);

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
  unitMotion.registerBrakeLight(PINBRAKELIGHT);
  #if (ScenarioStartStop == true)
  byte ms = unitMotion.registerMotionSequence(mskStraight);
  unitMotion.addMotionSequenceItem(ms, SPEEDEASY, edForward, tdNone, 1500);
  unitMotion.addMotionSequenceItem(ms, SPEEDEASY, edForward, tdNone, 500, flsBrake);
  unitMotion.addMotionSequenceItemStop(ms, 3000, flsBrake);
  #endif
  #if (ScenarioTurnLeft == true)
  byte ms = unitMotion.registerMotionSequence(mskLeft);
  unitMotion.addMotionSequenceItem(ms, SPEEDEASY, edForward, tdNone, 1000, flsLeft);
  unitMotion.addMotionSequenceItem(ms, SPEEDCURVE, edForward, tdLeft, 350, flsLeft);
  unitMotion.addMotionSequenceItem(ms, SPEEDEASY, edForward, tdNone, 1000);
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
