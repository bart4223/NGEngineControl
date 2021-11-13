#define PROD true //false,true

#define ScenarioCaveExplorer true  //false,true
#define ScenarioBotRetriever false //false,true

#include <NGMotionUnitControl.h>
#include <NGSerialNotification.h>
#include <NGLightSensor.h>
#include <NGFlashingLight.h>
#include <NGJingleHelloDude.h>
#include <NGJingleBackward.h>
#include <NGJingleAlarm.h>
#include <NGJingleThinking.h>
#include <NGJingleBoot.h>
#include <NGLaserCannon.h>
#include <NGMotionSequenceDefinitions.h>
#include <NGContactObjectRecognizer.h>
#include <NGUltrasonicObjectRecognizer.h>
#if (ScenarioCaveExplorer == true)
#include <NGCaveExplorer.h>
#endif
#if (ScenarioBotRetriever == true)
#include <NGBotRetriever.h>
#endif

#define _MOTION       "Motion"
#define MOTION        (char*)_MOTION
#define MOTIONADDRESS 0x21

#define ENGINEOFFSETLEFT    15
#define ENGINEOFFSETRIGHT  -15

#define PINLIGHTSENSOR       A0
#define PINSTARTUP           A1
#define PINCORLEFT           A2
#define PINCORRIGHT          A3
#define PINFREE00            A4
#define PINFREE01            A5
#define PINFREE02             0
#define PINFREE03             1
#define PINBRAKELIGHT         2
#define PINENGINERIGHT1       3
#define PINLIGHT              4
#define PINENGINELEFT1        5
#define PINENGINELEFT2        6
#define PINFLASHINGLIGHTLEFT  7
#define PINFLASHINGLIGHTRIGHT 8
#define PINENGINERIGHT2       9
#define PINULTRASONICTRIGGER 10
#define PINULTRASONICECHO    11
#define PINLASERCANNON       12
#define PINPIEZOSOUND        13

#define LIGHTSENSORDELAY      1000
#define LIGHTSENSORTHRESHOLD  650

#define FLASHINGLIGHTINTERVAL 250

#define ULTRASONICMAXDISTANCE 30

#define SPEEDEASY   200
#define SPEEDCURVE  150
#define SPEEDBACK   120

NGMotionUnitControl unitMotion = NGMotionUnitControl(MOTION, ENGINE_2, ENGINE_1, ENGINEOFFSETLEFT, ENGINEOFFSETRIGHT);
NGSerialNotification serialNotification = NGSerialNotification();
NGLightSensor lightSensor = NGLightSensor(PINLIGHTSENSOR);
NGFlashingLight flLeft = NGFlashingLight(PINFLASHINGLIGHTLEFT, FLASHINGLIGHTINTERVAL);
NGFlashingLight flRight = NGFlashingLight(PINFLASHINGLIGHTRIGHT, FLASHINGLIGHTINTERVAL);
NGJingleHelloDude jingleHelloDude = NGJingleHelloDude();
NGJingleBackward jingleBackward = NGJingleBackward();
NGJingleAlarm jingleAlarm = NGJingleAlarm();
NGJingleThinking jingleThinking = NGJingleThinking();
NGJingleBoot jingleBoot = NGJingleBoot();
NGContactObjectRecognizer corLeft = NGContactObjectRecognizer(PINCORLEFT);
NGContactObjectRecognizer corRight = NGContactObjectRecognizer(PINCORRIGHT);
NGUltrasonicObjectRecognizer corUS = NGUltrasonicObjectRecognizer(PINULTRASONICTRIGGER, PINULTRASONICECHO, ULTRASONICMAXDISTANCE);
NGLaserCannon lc = NGLaserCannon(PINLASERCANNON);
#if (ScenarioCaveExplorer == true)
NGCaveExplorer mimic = NGCaveExplorer();
#elif (ScenarioBotRetriever == true)
NGBotRetriever mimic = NGBotRetriever();
#endif

void setup() {
  setGlobalUnit(&unitMotion);
  unitMotion.registerNotification(&serialNotification);
  #if (PROD == true)
  unitMotion.registerBoot(&jingleBoot);
  unitMotion.registerStartup(PINSTARTUP, &jingleHelloDude);
  unitMotion.registerJingleBackward(&jingleBackward);
  unitMotion.registerJingleAlarm(&jingleAlarm);
  unitMotion.registerJingleThinking(&jingleThinking);
  unitMotion.registerLightSensor(&lightSensor, LIGHTSENSORTHRESHOLD, tlUnder, PINLIGHT, tvHigh, LIGHTSENSORDELAY);
  unitMotion.registerLightSensor(&lightSensor, LIGHTSENSORTHRESHOLD, tlUnder, PINLASERCANNON, tvHigh, LIGHTSENSORDELAY);
  #else
  unitMotion.registerLightSensor(&lightSensor, LIGHTSENSORTHRESHOLD, tlUnder, PINLIGHT, tvHigh);
  unitMotion.registerLightSensor(&lightSensor, LIGHTSENSORTHRESHOLD, tlUnder, PINLASERCANNON, tvHigh);
  #endif
  unitMotion.registerFlashingLights(&flLeft, &flRight);
  unitMotion.registerBrakeLight(PINBRAKELIGHT);
  unitMotion.registerLaserCannon(&lc);
  #if (ScenarioCaveExplorer == true)
  unitMotion.registerObjectRecognizer(ormpLeft, &corLeft);
  unitMotion.registerObjectRecognizer(ormpRight, &corRight);
  unitMotion.registerObjectRecognizer(ormpFront, &corUS);
  mimic.setBackwardCloseness(ULTRASONICMAXDISTANCE / 2);
  unitMotion.registerMotionMimic(&mimic);
  // forward
  DEF_MOTION_SEQUENCE_START;
  DEF_MOTION_SEQUENCE_BEGIN_STRAIGHT;
  DEF_MOTION_SEQUENCE_FORWARD(SPEEDEASY, 0);
  DEF_MOTION_SEQUENCE_END_STRAIGHT;
  // backward
  DEF_MOTION_SEQUENCE_BEGIN_BACK;
  DEF_MOTION_SEQUENCE_BACKWARD(SPEEDBACK, 500);
  DEF_MOTION_SEQUENCE_BACKWARD_WITH_BRAKE(SPEEDBACK, 1000);
  DEF_MOTION_SEQUENCE_STOP(1500);
  DEF_MOTION_SEQUENCE_END_BACK;
  // left
  DEF_MOTION_SEQUENCE_BEGIN_LEFT;
  DEF_MOTION_SEQUENCE_FORWARD_WITH_LIGHTLEFT(SPEEDCURVE, 250);
  DEF_MOTION_SEQUENCE_FORWARD_LEFT_WITH_LIGHT(SPEEDCURVE, 1250);
  DEF_MOTION_SEQUENCE_END_LEFT;
  // right
  DEF_MOTION_SEQUENCE_BEGIN_RIGHT;
  DEF_MOTION_SEQUENCE_FORWARD_WITH_LIGHTRIGHT(SPEEDCURVE, 250);
  DEF_MOTION_SEQUENCE_FORWARD_RIGHT_WITH_LIGHT(SPEEDCURVE, 1250);
  DEF_MOTION_SEQUENCE_END_RIGHT;
  #elif (ScenarioBotRetriever == true)
  unitMotion.registerMotionMimic(&mimic);
  // forward
  DEF_MOTION_SEQUENCE_START;
  DEF_MOTION_SEQUENCE_BEGIN_STRAIGHT;
  DEF_MOTION_SEQUENCE_FORWARD(SPEEDEASY, 2500);
  DEF_MOTION_SEQUENCE_END_STRAIGHT;
  // fullturn
  DEF_MOTION_SEQUENCE_BEGIN_FULLTURN;
  DEF_MOTION_SEQUENCE_FULLTURN(SPEEDCURVE, 550);
  DEF_MOTION_SEQUENCE_STOP_NONE(100);
  DEF_MOTION_SEQUENCE_END_FULLTURN;
  // stop
  DEF_MOTION_SEQUENCE_BEGIN_STOP;
  DEF_MOTION_SEQUENCE_FORWARD_WITH_BRAKE(SPEEDEASY, 500);
  DEF_MOTION_SEQUENCE_STOP_WITH_BRAKE(1000);
  DEF_MOTION_SEQUENCE_STOP_NONE(100);
  DEF_MOTION_SEQUENCE_END_STOP;
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
