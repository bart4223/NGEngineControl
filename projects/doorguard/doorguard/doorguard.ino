#define PROD false //false, true

#include <NGMemoryObserver.h>
#include <NGSimpleLED.h>
#include <Effects/NGSimpleLEDEffect.h>
#include <Apps/NGDoorGuardUnitControl.h>
#if (PROD != true)
#include <NGSerialNotification.h>
#endif

#define _DOORDGUARD       "Door Guard"
#define DOORDGUARD        (char*)_DOORDGUARD
#define DOORDGUARDADDRESS 0x24

#define PINLED1 6
#define PINLED2 7

#define OPENSTEPDELAY    150
#define CLOSESTEPDELAY   500
#define DOOROPENDELAY  10000
#define DOORCLOSEDELAY  2000

NGDoorGuardUnitControl unitDoordGuard = NGDoorGuardUnitControl(DOORDGUARD);
#if (PROD != true)
NGSerialNotification serialNotification = NGSerialNotification();
#endif

NGHallSensor hs = NGHallSensor();
NGSimpleLED led1 = NGSimpleLED(PINLED1);
NGSimpleLED led2 = NGSimpleLED(PINLED2);
NGSimpleLEDEffect seCloseOn = NGSimpleLEDEffect(slekFlash, CLOSESTEPDELAY);
NGSimpleLEDEffect seCloseOff = NGSimpleLEDEffect(slekNone);
NGSimpleLEDEffect seOpenOn = NGSimpleLEDEffect(slekAlternate, OPENSTEPDELAY);
NGSimpleLEDEffect seOpenOff = NGSimpleLEDEffect(slekNone);

void setup() {
  observeMemory(0);
  setGlobalUnit(&unitDoordGuard);
  // Effects
  seOpenOn.registerLED(&led1);
  seOpenOn.registerLED(&led2);
  seOpenOff.registerLED(&led1);
  seOpenOff.registerLED(&led2);
  seCloseOn.registerLED(&led1);
  seCloseOn.registerLED(&led2);
  seCloseOff.registerLED(&led1);
  seCloseOff.registerLED(&led2);
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