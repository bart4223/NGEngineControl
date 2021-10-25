#define PROD true  //false,true

#define ScenarioStartStop             false  //false,true
#define ScenarioForwardTurnLeftSoft   true   //false,true
#define ScenarioForwardTurnRightSoft  true   //false,true
#define ScenarioBackwardTurnLeftSoft  false  //false,true
#define ScenarioBackwardTurnRightSoft false  //false,true

#include <NGMotionUnitControl.h>
#include <NGSerialNotification.h>
#include <NGLightSensor.h>
#include <NGFlashingLight.h>
#include <NGJingleHelloDude.h>
#include <NGJingleBackward.h>
#include <NGJingleAlarm.h>
#include <NGMotionSequenceDefinitions.h>
#include <NGCaveExplorer.h>

#define _MOTION       "Motion"
#define MOTION        (char*)_MOTION
#define MOTIONADDRESS 0x21

#define ENGINEOFFSETLEFT    25
#define ENGINEOFFSETRIGHT  -25

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
#define SPEEDCURVE  150

NGMotionUnitControl unitMotion = NGMotionUnitControl(MOTION, ENGINE_2, ENGINE_1, ENGINEOFFSETLEFT, ENGINEOFFSETRIGHT);
NGSerialNotification serialNotification = NGSerialNotification();
NGLightSensor lightSensor = NGLightSensor(PINLIGHTSENSOR);
NGFlashingLight flLeft = NGFlashingLight(PINFLASHINGLIGHTLEFT, FLASHINGLIGHTINTERVAL);
NGFlashingLight flRight = NGFlashingLight(PINFLASHINGLIGHTRIGHT, FLASHINGLIGHTINTERVAL);
NGJingleHelloDude jingleHelloDude = NGJingleHelloDude();
NGJingleBackward jingleBackward = NGJingleBackward();
NGJingleAlarm jingleAlarm = NGJingleAlarm();
NGCaveExplorer caveExplorer = NGCaveExplorer();

void setup() {
  setGlobalUnit(&unitMotion);
  unitMotion.registerNotification(&serialNotification);
  #if (PROD == true)
  unitMotion.registerStartup(PINSTARTUP, &jingleHelloDude);
  unitMotion.registerJingleBackward(&jingleBackward);
  unitMotion.registerJingleAlarm(&jingleAlarm);
  unitMotion.registerLightSensor(&lightSensor, LIGHTSENSORTHRESHOLD, tlUnder, PINLIGHT, tvHigh, LIGHTSENSORDELAY);
  #else
  unitMotion.registerLightSensor(&lightSensor, LIGHTSENSORTHRESHOLD, tlUnder, PINLIGHT, tvHigh);
  #endif
  unitMotion.registerFlashingLights(&flLeft, &flRight);
  unitMotion.registerBrakeLight(PINBRAKELIGHT);
  //unitMotion.registerMotionMimic(&caveExplorer);
  DEF_MOTION_SEQUENCE_START;
  #if (ScenarioStartStop == true)
  DEF_MOTION_SEQUENCE_BEGIN_STRAIGHT;
  DEF_MOTION_SEQUENCE_FORWARD(SPEEDEASY, 1250);
  DEF_MOTION_SEQUENCE_FORWARD_WITH_BRAKE(SPEEDEASY, 750);
  DEF_MOTION_SEQUENCE_STOP_WITH_BRAKE(500);
  DEF_MOTION_SEQUENCE_STOP(2500);
  DEF_MOTION_SEQUENCE_END_STRAIGHT;
  #endif
  #if (ScenarioForwardTurnLeftSoft == true)
  DEF_MOTION_SEQUENCE_BEGIN_LEFT;
  DEF_MOTION_SEQUENCE_FORWARD_WITH_LIGHTLEFT(SPEEDEASY, 1000);
  DEF_MOTION_SEQUENCE_FORWARD_LEFT_WITH_LIGHT(SPEEDCURVE, 950);
  DEF_MOTION_SEQUENCE_FORWARD(SPEEDEASY, 1000);
  DEF_MOTION_SEQUENCE_END_LEFT;
  #endif
  #if (ScenarioForwardTurnRightSoft == true)
  DEF_MOTION_SEQUENCE_BEGIN_RIGHT;
  DEF_MOTION_SEQUENCE_FORWARD_WITH_LIGHTRIGHT(SPEEDEASY, 1000);
  DEF_MOTION_SEQUENCE_FORWARD_RIGHT_WITH_LIGHT(SPEEDCURVE, 950);
  DEF_MOTION_SEQUENCE_FORWARD(SPEEDEASY, 1000);
  DEF_MOTION_SEQUENCE_END_RIGHT;
  #endif
  #if (ScenarioBackwardTurnLeftSoft == true)
  DEF_MOTION_SEQUENCE_BEGIN_LEFT;
  DEF_MOTION_SEQUENCE_BACKWARD_WITH_LIGHTLEFT(SPEEDEASY, 1000);
  DEF_MOTION_SEQUENCE_BACKWARD_LEFT_WITH_LIGHT(SPEEDCURVE, 950);
  DEF_MOTION_SEQUENCE_BACKWARD(SPEEDEASY, 1000);
  DEF_MOTION_SEQUENCE_END_LEFT;
  #endif
  #if (ScenarioBackwardTurnRightSoft == true)
  DEF_MOTION_SEQUENCE_BEGIN_RIGHT;
  DEF_MOTION_SEQUENCE_BACKWARD_WITH_LIGHTRIGHT(SPEEDEASY, 1000);
  DEF_MOTION_SEQUENCE_BACKWARD_RIGHT_WITH_LIGHT(SPEEDCURVE, 950);
  DEF_MOTION_SEQUENCE_BACKWARD(SPEEDEASY, 1000);
  DEF_MOTION_SEQUENCE_END_RIGHT;
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
