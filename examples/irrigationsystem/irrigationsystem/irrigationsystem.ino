#include <NGIrrigationUnitControl.h>
#include <NGRealTimeClock.h>
#include <NGSerialNotification.h>
#include <NGOLEDNotification.h>

#define _IRRIGATION           "Irrigation"
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
NGSerialNotification serialNotification = NGSerialNotification();
NGOLEDNotification *oledNotification;
NGRealTimeClock rtc = NGRealTimeClock();

void setup() {
  setGlobalUnit(&unitIrrigation);
  unitIrrigation.registerNotification(&serialNotification);
  oledNotification = new NGOLEDNotification(OLEDTYPE, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  unitIrrigation.registerNotification(oledNotification);
  rtc.initialize(true); //One times!!!
  unitIrrigation.registerRealTimeClock(&rtc);
  int sms = unitIrrigation.registerSoilMoistureSensor(PINSOILMOISTURESENSOR);
  int pump = unitIrrigation.registerPump(PINPUMP);
  unitIrrigation.initialize();
  unitIrrigation.setWorkMode(wmObserveMemory);
  unitIrrigation.startUp();
  unitIrrigation.clearInfo();
}

void loop() {
  unitIrrigation.processingLoop();
}
