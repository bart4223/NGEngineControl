#define PROD true //false,true

#include <NGMotionUnitControl.h>
#include <NGSimpleMotionControl.h>
#include <NGRealTimeClock.h>
#include <NGSerialNotification.h>
#include <NGOLEDNotification.h>
#include <NGMorseToneNotification.h>
#include <NGQuestionDialog.h>
#include <NGLightSensor.h>
#include <NGFlashingLight.h>
#include <NGJingleBoot.h>
#include <NGJingleBeep.h>
#include <NGJingleHelloDude.h>
#include <NGJingleJingleBells.h>
#include <NGJingleBackward.h>
#include <NGJingleAlarm.h>
#include <NGJingleThinking.h>
#include <NGLaserCannon.h>
#include <NGMotionSequenceDefinitions.h>
#include <NGContactObjectRecognizer.h>
#include <NGUltrasonicObjectRecognizer.h>
#include <NGVoidMotionMimic.h>
#include <NGCaveExplorer.h>
#include <NGBotRetriever.h>

#define _BUGGY           "Buggy"
#define BUGGY            (char*)_BUGGY
#define BUGGYADDRESS     0x21

#if (PROD == true)
#define OLED64
#else
#define OLED32
#endif

#define OLEDADDRESS       0x3C
#define OLEDCOLUMNS       16
#ifdef OLED64
#define OLEDTYPE          ot128x64
#define OLEDLINES         8
#define OLEDLINEFACTOR    4
#endif
#ifdef OLED32
#define OLEDTYPE          ot128x32
#define OLEDLINES         4
#define OLEDLINEFACTOR    2
#endif

#define PINLIGHTSENSOR          A0
#define PINSTARTUP              A1
#define PINCORLEFT              A2
#define PINCORRIGHT             A3
#define PINFREE00               A4
#define PINFREE01               A5
#define PINFREE02               A6
#define PINFREE03               A7
#define PINQUESTIONDLGNO        A8
#define PINQUESTIONDLGYES       A9
#define PINFREE04                0
#define PINFREE05                1
#define PINBRAKELIGHT            2
#define PINENGINERIGHT1          3
#define PINLIGHT                 4
#define PINENGINELEFT1           5
#define PINENGINELEFT2           6
#define PINFLASHINGLIGHTLEFT     7
#define PINFLASHINGLIGHTRIGHT    8
#define PINENGINERIGHT2          9
#define PINULTRASONICTRIGGER    10
#define PINULTRASONICECHO       11
#define PINLASERCANNON          12
#define PINPIEZOSOUND           13
#define PINBACKWARDLIGHT        22

#define LIGHTSENSORDELAY      1000
#define LIGHTSENSORTHRESHOLD   650

#define FLASHINGLIGHTINTERVAL  250

#define ULTRASONICMAXDISTANCE   30

#define ENGINEOFFSETLEFT    15
#define ENGINEOFFSETRIGHT  -15

#define SPEEDEASY     200
#define SPEEDCURVE    150
#define SPEEDBACK     120

enum mimicScenario {msVoid, msCaveExplorer, msBotRetriever};

NGCustomMotionControl *motionControl = new NGSimpleMotionControl(new NGSteeringControl(ENGINE_2, ENGINE_1, ENGINEOFFSETLEFT, ENGINEOFFSETRIGHT));
NGMotionUnitControl unitBuggy = NGMotionUnitControl(BUGGY, motionControl);
NGSerialNotification serialNotification = NGSerialNotification();
NGOLEDNotification *oledNotification;
NGMorseToneNotification morseToneNotification = NGMorseToneNotification();
NGRealTimeClock rtc = NGRealTimeClock();
NGQuestionDialog dlgQuestion = NGQuestionDialog(PINQUESTIONDLGYES, PINQUESTIONDLGNO);
NGLightSensor lightSensor = NGLightSensor(PINLIGHTSENSOR);
NGFlashingLight flLeft = NGFlashingLight(PINFLASHINGLIGHTLEFT, FLASHINGLIGHTINTERVAL);
NGFlashingLight flRight = NGFlashingLight(PINFLASHINGLIGHTRIGHT, FLASHINGLIGHTINTERVAL);
NGJingleBoot jingleBoot = NGJingleBoot();
NGJingleBeep jingleBeep = NGJingleBeep();
NGJingleHelloDude jingleHelloDude = NGJingleHelloDude();
NGJingleJingleBells jingleJingleBells = NGJingleJingleBells();
NGJingleBackward jingleBackward = NGJingleBackward();
NGJingleAlarm jingleAlarm = NGJingleAlarm();
NGJingleThinking jingleThinking = NGJingleThinking();
NGContactObjectRecognizer corLeft = NGContactObjectRecognizer(PINCORLEFT);
NGContactObjectRecognizer corRight = NGContactObjectRecognizer(PINCORRIGHT);
NGUltrasonicObjectRecognizer corUS = NGUltrasonicObjectRecognizer(PINULTRASONICTRIGGER, PINULTRASONICECHO, ULTRASONICMAXDISTANCE);
NGLaserCannon lc = NGLaserCannon(PINLASERCANNON);

void setup() {
  setGlobalUnit(&unitBuggy);
  unitBuggy.registerBeep(&jingleBeep);
  unitBuggy.registerNotification(&serialNotification);
  oledNotification = new NGOLEDNotification(OLEDTYPE, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  unitBuggy.registerNotification(oledNotification);
  unitBuggy.registerNotification(&morseToneNotification);
  rtc.initialize();
  #if (PROD == true)
  unitBuggy.registerRealTimeClock(&rtc);
  #endif
  unitBuggy.registerBoot(&jingleBoot);
  #if (PROD == true)
  if (rtc.isXMas()) {
    unitBuggy.registerStartup(PINSTARTUP, &jingleJingleBells, 1);
  } else {
    unitBuggy.registerStartup(PINSTARTUP, &jingleHelloDude);
  }
  unitBuggy.registerMotionInterruption(PINSTARTUP);
  unitBuggy.registerJingleBackward(&jingleBackward);
  unitBuggy.registerJingleAlarm(&jingleAlarm);
  unitBuggy.registerJingleThinking(&jingleThinking);
  unitBuggy.registerLightSensor(&lightSensor, LIGHTSENSORTHRESHOLD, tlUnder, PINLIGHT, tvHigh, LIGHTSENSORDELAY);
  unitBuggy.registerLightSensor(&lightSensor, LIGHTSENSORTHRESHOLD, tlUnder, PINLASERCANNON, tvHigh, LIGHTSENSORDELAY);
  #else
  unitBuggy.registerLightSensor(&lightSensor, LIGHTSENSORTHRESHOLD, tlUnder, PINLIGHT, tvHigh);
  unitBuggy.registerLightSensor(&lightSensor, LIGHTSENSORTHRESHOLD, tlUnder, PINLASERCANNON, tvHigh);
  #endif
  unitBuggy.registerFlashingLights(&flLeft, &flRight);
  unitBuggy.registerBrakeLight(PINBRAKELIGHT);
  unitBuggy.registerBackwardLight(PINBACKWARDLIGHT);
  unitBuggy.registerLaserCannon(&lc);
  #if (PROD == true)
  bool doTest = true;
  unitBuggy.testSequenceStart();
  unitBuggy.clearInfo();
  unitBuggy.writeInfo("Test Sequence Stop?");
  while (!dlgQuestion.confirm()) {
    unitBuggy.beep();
  }
  unitBuggy.beep();
  unitBuggy.testSequenceStop();
  #endif
  mimicScenario ms = msVoid;
  unitBuggy.clearInfo();
  #if (PROD == true)
  unitBuggy.writeInfo("Mimic \"Cave-Explorer\"?");
  if (dlgQuestion.confirm()) {
    unitBuggy.beep();
    ms = msCaveExplorer;
  } else {
    unitBuggy.beep();
    unitBuggy.clearInfo();
    unitBuggy.writeInfo("Mimic \"Bot-Retriever\"?");
    if (dlgQuestion.confirm()) {
      ms = msBotRetriever;
    }
    unitBuggy.beep();
  }
  #endif
  DEF_MOTION_SEQUENCE_START;
  switch (ms) {
    case msVoid:
      unitBuggy.writeInfo("\"Void\" Mimic choosed!");
      unitBuggy.registerMotionMimic(new NGVoidMotionMimic());
      break;
    case msCaveExplorer:
      unitBuggy.writeInfo("...Mimic \"Cave-Explorer\" choosed");
      unitBuggy.registerObjectRecognizer(ormpLeft, &corLeft);
      unitBuggy.registerObjectRecognizer(ormpRight, &corRight);
      unitBuggy.registerObjectRecognizer(ormpFront, &corUS);
      NGCaveExplorer *mimicCaveExplorer = new NGCaveExplorer();
      mimicCaveExplorer->setBackwardCloseness(ULTRASONICMAXDISTANCE / 2);
      unitBuggy.registerMotionMimic(mimicCaveExplorer);
      // forward
      DEF_MOTION_SEQUENCE_BEGIN_STRAIGHT(unitBuggy);
      DEF_MOTION_SEQUENCE_FORWARD(unitBuggy, SPEEDEASY, 0);
      DEF_MOTION_SEQUENCE_END_STRAIGHT;
      // backward
      DEF_MOTION_SEQUENCE_BEGIN_BACK(unitBuggy);
      DEF_MOTION_SEQUENCE_BACKWARD(unitBuggy, SPEEDBACK, 500);
      DEF_MOTION_SEQUENCE_BACKWARD_WITH_BRAKE(unitBuggy, SPEEDBACK, 1000);
      DEF_MOTION_SEQUENCE_STOP(unitBuggy, 1500);
      DEF_MOTION_SEQUENCE_END_BACK;
      // left
      DEF_MOTION_SEQUENCE_BEGIN_LEFT(unitBuggy);
      DEF_MOTION_SEQUENCE_FORWARD_WITH_LIGHTLEFT(unitBuggy, SPEEDCURVE, 250);
      DEF_MOTION_SEQUENCE_FORWARD_LEFT_WITH_LIGHT(unitBuggy, SPEEDCURVE, 1250);
      DEF_MOTION_SEQUENCE_END_LEFT;
      // right
      DEF_MOTION_SEQUENCE_BEGIN_RIGHT(unitBuggy);
      DEF_MOTION_SEQUENCE_FORWARD_WITH_LIGHTRIGHT(unitBuggy, SPEEDCURVE, 250);
      DEF_MOTION_SEQUENCE_FORWARD_RIGHT_WITH_LIGHT(unitBuggy, SPEEDCURVE, 1250);
      DEF_MOTION_SEQUENCE_END_RIGHT;
      break;
    case msBotRetriever:
      unitBuggy.writeInfo("...Mimic \"Bot-Retriever\" choosed");
      unitBuggy.registerMotionMimic(new NGBotRetriever());
      // forward
      DEF_MOTION_SEQUENCE_BEGIN_STRAIGHT(unitBuggy);
      DEF_MOTION_SEQUENCE_FORWARD(unitBuggy, SPEEDEASY, 2500);
      DEF_MOTION_SEQUENCE_END_STRAIGHT;
      // fullturn
      DEF_MOTION_SEQUENCE_BEGIN_FULLTURN(unitBuggy);
      DEF_MOTION_SEQUENCE_FULLTURN(unitBuggy, SPEEDCURVE, 550);
      DEF_MOTION_SEQUENCE_STOP_NONE(unitBuggy, 100);
      DEF_MOTION_SEQUENCE_END_FULLTURN;
      // stop
      DEF_MOTION_SEQUENCE_BEGIN_STOP(unitBuggy);
      DEF_MOTION_SEQUENCE_FORWARD_WITH_BRAKE(unitBuggy, SPEEDEASY, 500);
      DEF_MOTION_SEQUENCE_STOP_WITH_BRAKE(unitBuggy, 1000);
      DEF_MOTION_SEQUENCE_STOP_NONE(unitBuggy, 100);
      DEF_MOTION_SEQUENCE_END_STOP;
      break;
  }
  unitBuggy.initialize();
  #if (PROD == false)
  unitBuggy.setWorkMode(wmObserveMemory);
  #endif
  unitBuggy.startUp();
  unitBuggy.clearInfo();
  if (ms == msVoid) {
    unitBuggy.writeInfo("\"Void\" scenario(#SOS#)!");
  } else {
    unitBuggy.writeInfo("Hi folks(#Hello#), moves...");
  }
}

void loop() {
  unitBuggy.processingLoop();
}
