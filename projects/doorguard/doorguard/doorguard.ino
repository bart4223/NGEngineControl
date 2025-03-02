#define PROD true //false, true

#include <NGMemoryObserver.h>
#include <NGColorLEDStrip.h>
#include <Effects/NGSimpleColorLEDStripEffect.h>
#include <Apps/NGDoorGuardUnitControl.h>
#if (PROD != true)
#include <NGSerialNotification.h>
#endif

#define _DOORDGUARD       "Door Guard"
#define DOORDGUARD        (char*)_DOORDGUARD
#define DOORDGUARDADDRESS 0x24

#define PINLEDSTRIP       8
#define LEDSTRIP8_PIXELS  8
#define LEDSTRIP8_ROWS    1

#if (PROD != true)
#define BRIGHTNESS 0.05
#else
#define BRIGHTNESS 0.25
#endif

#define OPENSTEPDELAY    150
#define CLOSESTEPDELAY   500
#define DOOROPENDELAY  10000
#define DOORCLOSEDELAY  2000

NGDoorGuardUnitControl unitDoordGuard = NGDoorGuardUnitControl(DOORDGUARD);
#if (PROD != true)
NGSerialNotification serialNotification = NGSerialNotification();
#endif

NGHallSensor hs = NGHallSensor();
NGColorLEDStrip cls = NGColorLEDStrip(PINLEDSTRIP, LEDSTRIP8_PIXELS, LEDSTRIP8_ROWS);
NGSimpleColorLEDStripEffect seCloseOn = NGSimpleColorLEDStripEffect(&cls, slsekFlash);
NGSimpleColorLEDStripEffect seCloseOff = NGSimpleColorLEDStripEffect(&cls, slsekNone);
NGSimpleColorLEDStripEffect seOpenOn = NGSimpleColorLEDStripEffect(&cls, slsekFlash);
NGSimpleColorLEDStripEffect seOpenOff = NGSimpleColorLEDStripEffect(&cls, slsekNone);

void setup() {
  observeMemory(0);
  setGlobalUnit(&unitDoordGuard);
  // LED Strip
  cls.setBrightness(BRIGHTNESS);
  // Effects
  seCloseOn.setStepDelay(CLOSESTEPDELAY);
  seCloseOn.setEffectColors(COLOR_GREEN);
  seOpenOn.setStepDelay(OPENSTEPDELAY);
  seOpenOn.setEffectColors(COLOR_RED);
  // App
  #if (PROD != true)
    unitDoordGuard.registerNotification(&serialNotification);
  #endif
  byte doorOne = unitDoordGuard.registerDoor(&hs, dekFinite, &seOpenOn, &seOpenOff, dekFinite, &seCloseOn, &seCloseOff);
  unitDoordGuard.setDoorDelay(doorOne, DOOROPENDELAY, DOORCLOSEDELAY);
  unitDoordGuard.initialize();
  #if (PROD == true)
    unitDoordGuard.setLogging(false);
    unitDoordGuard.setWorkMode(wmNone);
  #else
    unitDoordGuard.setLogging(true);
    unitDoordGuard.setWorkMode(wmObserveMemory);
  #endif
  unitDoordGuard.startUp();
  unitDoordGuard.clearInfo();
  observeMemory(0);
}

void loop() {
  unitDoordGuard.processingLoop();
}