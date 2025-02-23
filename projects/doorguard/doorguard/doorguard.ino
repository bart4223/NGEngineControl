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

#define DELAY     1000
#define STEPDELAY  150

NGDoorGuardUnitControl unitDoordGuard = NGDoorGuardUnitControl(DOORDGUARD);
#if (PROD != true)
NGSerialNotification serialNotification = NGSerialNotification();
#endif

NGHallSensor hs = NGHallSensor();
NGSimpleLED led1 = NGSimpleLED(PINLED1);
NGSimpleLED led2 = NGSimpleLED(PINLED2);
NGSimpleLEDEffect seOff = NGSimpleLEDEffect(slekNone);
NGSimpleLEDEffect seOn = NGSimpleLEDEffect(slekAlternate, STEPDELAY);

void setup() {
  observeMemory(0);
  setGlobalUnit(&unitDoordGuard);
  // Effects
  seOn.registerLED(&led1);
  seOn.registerLED(&led2);
  seOff.registerLED(&led1);
  seOff.registerLED(&led2);
  // App
  #if (PROD != true)
    unitDoordGuard.registerNotification(&serialNotification);
  #endif
  unitDoordGuard.registerDoor(&hs, &seOn, &seOff);
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