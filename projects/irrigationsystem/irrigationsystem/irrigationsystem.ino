#define PROD true //false,true

#include <NGIrrigationUnitControl.h>
#include <NGRealTimeClock.h>
#include <NGSerialNotification.h>
#include <NGOLEDNotification.h>
#include <NGJingleBoot.h>

#define _IRRIGATION           "Bonsai"
#define IRRIGATION            (char*)_IRRIGATION
#define IRRIGATIONADDRESS     0x22

#define OLEDADDRESS       0x3C
#define OLEDCOLUMNS       16
#define OLEDTYPE          ot128x32
#define OLEDLINES         4
#define OLEDLINEFACTOR    2

#define PINSOILMOISTURESENSOR   A0
#define PINPUMP   9

NGIrrigationUnitControl unitIrrigation = NGIrrigationUnitControl(IRRIGATION);
#if (PROD == false)
NGSerialNotification serialNotification = NGSerialNotification();
#endif
NGOLEDNotification *oledNotification;
NGRealTimeClock rtc = NGRealTimeClock();
NGJingleBoot jingleBoot = NGJingleBoot();

void setup() {
  setGlobalUnit(&unitIrrigation);
  #if (PROD == false)
  unitIrrigation.registerNotification(&serialNotification);
  #endif
  oledNotification = new NGOLEDNotification(OLEDTYPE, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  unitIrrigation.registerNotification(oledNotification);
  rtc.initialize(false);
  unitIrrigation.registerBoot(&jingleBoot);
  unitIrrigation.registerRealTimeClock(&rtc);
  unitIrrigation.registerIrrigation(PINPUMP, 720, 1);
  unitIrrigation.initialize();
  #if (PROD == true)
  unitIrrigation.setWorkMode(wmNone);
  #else
  unitIrrigation.setWorkMode(wmObserveMemory);
  #endif
  unitIrrigation.startUp();
  unitIrrigation.clearInfo();
}

void loop() {
  unitIrrigation.processingLoop();
}
