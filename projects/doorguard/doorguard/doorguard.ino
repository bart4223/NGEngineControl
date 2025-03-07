#define PROD true //false, true

#include <NGMemoryObserver.h>
#include <NGColorLEDStrip.h>
#include <Effects/NGSimpleColorLEDStripEffect.h>
#include <Apps/NGDoorGuardUnitControl.h>
#include <Sensors/NGSimpleDigitalSensor.h>
#if (PROD != true)
#include <NGSerialNotification.h>
#endif

#define _DOORDGUARD       "Door Guard"
#define DOORDGUARD        (char*)_DOORDGUARD
#define DOORDGUARDADDRESS 0x24

#define PINLEDSTRIP       7
#define LEDSTRIP8_PIXELS 12
#define LEDSTRIP8_ROWS    1

#define PINDSONE  4
#define PINDSTWO  5

#if (PROD != true)
#define BRIGHTNESS 0.05
#else
#define BRIGHTNESS 0.25
#endif

#define OPENSTEPDELAYFAST   50
#define OPENSTEPDELAY      150
#define CLOSESTEPDELAY     500
#define DOOROPENDELAY    10000
#define DOORCLOSEDELAY    2000

NGDoorGuardUnitControl unitDoordGuard = NGDoorGuardUnitControl(DOORDGUARD);
#if (PROD != true)
NGSerialNotification serialNotification = NGSerialNotification();
#endif

NGHallSensor hs = NGHallSensor();
NGColorLEDStrip cls = NGColorLEDStrip(PINLEDSTRIP, LEDSTRIP8_PIXELS, LEDSTRIP8_ROWS);
NGSimpleDigitalSensor dsOne = NGSimpleDigitalSensor(PINDSONE);
NGSimpleDigitalSensor dsTwo = NGSimpleDigitalSensor(PINDSTWO);
NGSimpleColorLEDStripEffect seCloseOn = NGSimpleColorLEDStripEffect(&cls, slsekFlash);
NGSimpleColorLEDStripEffect seCloseOff = NGSimpleColorLEDStripEffect(&cls);
NGSimpleColorLEDStripEffect seOpenOn = NGSimpleColorLEDStripEffect(&cls);
NGSimpleColorLEDStripEffect seOpenOff = NGSimpleColorLEDStripEffect(&cls);

void setup() {
  observeMemory(0);
  setGlobalUnit(&unitDoordGuard);
  // Digital sensors
  dsOne.initialize();
  dsTwo.initialize();
  // LED Strip
  cls.setBrightness(BRIGHTNESS);
  // Effects
  seCloseOn.setStepDelay(CLOSESTEPDELAY);
  seCloseOn.setEffectColors(COLOR_GREEN);
  seOpenOn.setStepDelay(OPENSTEPDELAY);
  seOpenOn.setEffectColors(COLOR_RED);
  if (dsOne.isOn()) {
    seOpenOn.setKind(slsekRunning);
    seOpenOn.setStepDelay(OPENSTEPDELAYFAST);
  } else if (dsTwo.isOn()) {
    seOpenOn.setKind(slsekRandom);
    seOpenOn.setStepDelay(OPENSTEPDELAY);
  } else {
    seOpenOn.setKind(slsekAlternate);
    seOpenOn.setStepDelay(OPENSTEPDELAY);
  }
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