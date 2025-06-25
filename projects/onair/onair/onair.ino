#define PROD false //false, true

#include <NGEngineCore.h>
#include <Visuals/NGCircleLEDStrip.h>
#include <Apps/NGOnAirUnitControl.h>
#include <Effects/NGSimpleCircleLEDStripEffect.h>
#if (PROD != true)
#include <NGSerialNotification.h>
#endif

#define _ONAIR       "OnAir"
#define ONAIR        (char*)_ONAIR
#define ONAIRADDRESS 0x26

#define SR_LATCHPIN  4
#define SR_CLOCKPIN  5
#define SR_DATAPIN   3

#define RBONE_KEYOFFSET 0
#define RBONE_STARTKEY  1

#define KEY1PIN            9
#define KEY1ID            42
#define KEY2PIN           10
#define KEY2ID            43
#define KEY3PIN           11
#define KEY3ID            44
#define KEY4PIN           12
#define KEY4ID            45

#define KEYDELAY    500

#define LEDSTRIP_PIN           8
#define LEDSTRIP_PIXELS      113
#define LEDSTRIP_RADIUS        7
#define LEDSTRIP_BRIGHTNESS 0.05

#define EFFECTONE_STEPDELAY   1000
#define EFFECTTWO_STEPDELAY     50
#define EFFECTTHREE_STEPDELAY   50

NG8BitShiftRegister *srRBOne = new NG8BitShiftRegister(SR_LATCHPIN, SR_CLOCKPIN, SR_DATAPIN);
NGRadioButtons rbOne = NGRadioButtons(srRBOne, RBONE_KEYOFFSET, RBONE_STARTKEY);

NGCircleLEDStrip cls = NGCircleLEDStrip(LEDSTRIP_PIN, LEDSTRIP_PIXELS, LEDSTRIP_RADIUS);
NGOnAirUnitControl unitOnAir = NGOnAirUnitControl(ONAIR);
#if (PROD != true)
NGSerialNotification serialNotification = NGSerialNotification();
#endif

NGSimpleCircleLEDStripEffect *effectOne = new NGSimpleCircleLEDStripEffect(&cls);
NGSimpleCircleLEDStripEffect *effectTwo = new NGSimpleCircleLEDStripEffect(&cls, sclsekPulse);
NGSimpleCircleLEDStripEffect *effectThree = new NGSimpleCircleLEDStripEffect(&cls, sclsekPulse);

void setup() {
  observeMemory(0);
  setGlobalUnit(&unitOnAir);
  // Radio Buttons One
  rbOne.registerCallback(&RadioButtonsCallback);
  rbOne.registerKey(KEY1PIN, KEY1ID, KEYDELAY);
  rbOne.registerKey(KEY2PIN, KEY2ID, KEYDELAY);
  rbOne.registerKey(KEY3PIN, KEY3ID, KEYDELAY);
  rbOne.registerKey(KEY4PIN, KEY4ID, KEYDELAY);
  rbOne.initialize();
  // Circle LED Strip
  cls.registerRadius(1, 0);  // 1 Pixel
  cls.registerRadius(2, 1);  // 8 Pixel
  cls.registerRadius(3, 9);  // 12 Pixel
  cls.registerRadius(4, 21); // 16 Pixel
  cls.registerRadius(5, 37); // 20 Pixel
  cls.registerRadius(6, 57); // 24 Pixel
  cls.registerRadius(7, 81); // 32 Pixel
  cls.setAngleOffset(180);
  cls.initialize(LEDSTRIP_BRIGHTNESS);
  #if (PROD != true)
  cls.setLogging(true);
  #endif
  // Effects
  effectOne->setStepDelay(EFFECTONE_STEPDELAY);
  effectTwo->setStepDelay(EFFECTTWO_STEPDELAY);
  effectTwo->setEffectColors(COLOR_GREEN);
  effectThree->setStepDelay(EFFECTTHREE_STEPDELAY);
  effectThree->setEffectColors(COLOR_BLUE, COLOR_YELLOW);
  // App
  #if (PROD != true)
  unitOnAir.registerNotification(&serialNotification);
  #endif
  unitOnAir.registerEffect(effectOne);
  unitOnAir.registerEffect(effectTwo);
  unitOnAir.registerEffect(effectThree);
  unitOnAir.initialize();
  #if (PROD == true)
  unitOnAir.setLogging(false);
  unitOnAir.setWorkMode(wmNone);
  #else
  unitOnAir.setLogging(true);
  unitOnAir.setWorkMode(wmObserveMemory);
  #endif
  unitOnAir.startUp();
  unitOnAir.clearInfo();
  observeMemory(0);
}

void loop() {
  rbOne.processingLoop();
  unitOnAir.processingLoop();
}

void RadioButtonsCallback(byte id) {
  switch(id) {
    case KEY1ID:
      unitOnAir.setCurrentEffect(0);  
      rbOne.resetRadioButtons();
      break;
    case KEY2ID:
      unitOnAir.setCurrentEffect(1);
      break;
    case KEY3ID:
      unitOnAir.setCurrentEffect(2);
      break;
    case KEY4ID:
      unitOnAir.setCurrentEffect(0);
      break;
  }
}