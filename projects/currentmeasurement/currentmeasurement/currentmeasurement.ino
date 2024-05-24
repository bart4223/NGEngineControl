#define PROD true //false,true

#include <NGCurrentMeasurementUnitControl.h>
#if (PROD != true)
#include <NGSerialNotification.h>
#endif
#include <NGOLEDNotification.h>

#define _CURRENT           "Current Measurement"
#define CURRENT            (char*)_CURRENT
#define CURRENTADDRESS     0x23

#define SENSORPIN            A0
#define SENSORDELAY         500
#define DISPLAYREFRESHRATE 2000

#define OLEDADDRESS       0x3C
#define OLEDCOLUMNS       16
#define OLEDTYPE          ot128x32
#define OLEDLINES         4
#define OLEDLINEFACTOR    2

NGCurrentMeasurementUnitControl unitCurrent = NGCurrentMeasurementUnitControl(CURRENT);
#if (PROD != true)
NGSerialNotification serialNotification = NGSerialNotification();
#endif
NGOLEDNotification *oledNotification;

void setup() {
  setGlobalUnit(&unitCurrent);
  #if (PROD != true)
    unitCurrent.registerNotification(&serialNotification);
  #endif
  oledNotification = new NGOLEDNotification(OLEDTYPE, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  unitCurrent.registerNotification(oledNotification);
  unitCurrent.setDisplaySensorInterval(DISPLAYREFRESHRATE);
  unitCurrent.registerSensor(cst20Ampere, SENSORPIN, SENSORDELAY);
  unitCurrent.initialize();
  #if (PROD == true)
    unitCurrent.setWorkMode(wmNone);
  #else
    unitCurrent.setWorkMode(wmObserveMemory);
  #endif
  unitCurrent.startUp();
  unitCurrent.clearInfo();
}

void loop() {
  unitCurrent.processingLoop();
}
