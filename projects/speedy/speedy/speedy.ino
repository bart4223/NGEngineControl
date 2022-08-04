#define PROD false  //false,true

#include <IRremote.h>
#include <NGCentralUnitControl.h>
#include <NGMotionUnitControl.h>
#include <NGOLEDNotification.h>
#if (PROD == false)
#include <NGSerialNotification.h>
#endif

#define _CENTRAL  "Speedy"
#define CENTRAL    (char*)_CENTRAL

#define _MOTION       "Motion"
#define MOTION        (char*)_MOTION

#define OLEDADDRESS       0x3C
#define OLEDCOLUMNS       16
#define OLEDTYPE          ot128x64
#define OLEDLINES         8
#define OLEDLINEFACTOR    4

#define IRREMOTE 2

IRrecv _irrecv(IRREMOTE);
NGCentralUnitControl unitCentral = NGCentralUnitControl(CENTRAL);
NGMotionUnitControl unitMotion = NGMotionUnitControl(MOTION);
NGOLEDNotification *oledNotification;
#if (PROD == false)
NGSerialNotification notificationSerial = NGSerialNotification();
#endif

void setup() {
  _irrecv.enableIRIn();
  setGlobalUnit(&unitCentral);
  oledNotification = new NGOLEDNotification(OLEDTYPE, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  unitCentral.registerNotification(oledNotification);
  #if (PROD == false)
  unitCentral.registerNotification(&notificationSerial);
  #endif
  unitCentral.registerUnit(MOTION, &unitMotion);
  unitCentral.initialize();
  #if (PROD == false)
  unitCentral.setWorkMode(wmObserveMemory);
  #endif
  unitCentral.clearInfo();
}

void loop() {
  if (_irrecv.decode()) {
    unitCentral.setIRRemoteData(_irrecv.decodedIRData.protocol,_irrecv.decodedIRData.address,_irrecv.decodedIRData.command);
    _irrecv.resume();
  }
  unitCentral.processingLoop();
}
