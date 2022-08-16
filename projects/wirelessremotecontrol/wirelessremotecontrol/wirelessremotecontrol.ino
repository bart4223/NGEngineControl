#define PROD false //false,true

#include <NGWirelessRemoteUnitControl.h>
#include <NGSerialNotification.h>
#include <NGOLEDNotification.h>

#define _REMOTE           "Wireless Remote"
#define REMOTE            (char*)_REMOTE
#define REMOTEADDRESS     0x23

#define OLEDADDRESS       0x3C
#define OLEDCOLUMNS       16
#define OLEDTYPE          ot128x32
#define OLEDLINES         4
#define OLEDLINEFACTOR    2

NGWirelessRemoteUnitControl unitRemote = NGWirelessRemoteUnitControl(REMOTE);
NGSerialNotification serialNotification = NGSerialNotification();
NGOLEDNotification *oledNotification;

void setup() {
  setGlobalUnit(&unitRemote);
  #if (PROD != true)
    unitRemote.registerNotification(&serialNotification);
  #endif
  oledNotification = new NGOLEDNotification(OLEDTYPE, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  unitRemote.registerNotification(oledNotification);
  unitRemote.initialize();
  #if (PROD == true)
    unitRemote.setWorkMode(wmNone);
  #else
    unitRemote.setWorkMode(wmObserveMemory);
  #endif
  unitRemote.startUp();
  unitRemote.clearInfo();
}

void loop() {
  unitRemote.processingLoop();
}
