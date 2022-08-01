#define PROD false  //false,true

#include <IRremote.h>
#if (PROD == false)
#include <NGSerialNotification.h>
#endif
#include <NGCentralUnitControl.h>

#define _CENTRAL  "Speedy"
#define CENTRAL    (char*)_CENTRAL

#define IRREMOTE 2

#if (PROD == false)
NGSerialNotification notificationSerial = NGSerialNotification();
#endif
NGCentralUnitControl unitCentral = NGCentralUnitControl(CENTRAL);
IRrecv _irrecv(IRREMOTE);

void setup() {
  _irrecv.enableIRIn();
  setGlobalUnit(&unitCentral);
  #if (PROD == false)
  unitCentral.registerNotification(&notificationSerial);
  #endif
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
