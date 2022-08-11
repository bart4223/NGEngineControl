#define PROD false  //false,true

#include <IRremote.h>
#include <NGMotionUnitControl.h>
#include <NGSimpleMotionControl.h>
#include <NGCarSteeringControl.h>
#include <NGOLEDNotification.h>
#if (PROD == false)
#include <NGSerialNotification.h>
#endif
#include <NGMotionSequenceDefinitions.h>

#define _MOTION  "Speedy"
#define MOTION    (char*)_MOTION

#define OLEDADDRESS       0x3C
#define OLEDCOLUMNS       16
#define OLEDTYPE          ot128x64
#define OLEDLINES         8
#define OLEDLINEFACTOR    4

#define IRREMOTE    2

#define SPEEDEASY   100

IRrecv _irrecv(IRREMOTE);
NGMotionUnitControl unitSpeedy = NGMotionUnitControl(MOTION, new NGSimpleMotionControl(new NGCarSteeringControl()));
NGOLEDNotification *oledNotification;
#if (PROD == false)
NGSerialNotification notificationSerial = NGSerialNotification();
#endif

void setup() {
  _irrecv.enableIRIn();
  setGlobalUnit(&unitSpeedy);
  oledNotification = new NGOLEDNotification(OLEDTYPE, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  unitSpeedy.registerNotification(oledNotification);
  #if (PROD == false)
  unitSpeedy.registerNotification(&notificationSerial);
  #endif
  unitSpeedy.registerIRRemoteFunction(ftUp, IRP_APPLE_2, IRA_APPLE, IRC_APPLE_UP);
  DEF_MOTION_SEQUENCE_START;
  // forward
  DEF_MOTION_SEQUENCE_BEGIN_STRAIGHT(unitSpeedy);
  DEF_MOTION_SEQUENCE_FORWARD(unitSpeedy, SPEEDEASY, 500);
  DEF_MOTION_SEQUENCE_END_STRAIGHT;
  unitSpeedy.initialize();
  #if (PROD == false)
  unitSpeedy.setWorkMode(wmObserveMemory);
  #endif
  unitSpeedy.startUp();
  unitSpeedy.clearInfo();
}

void loop() {
  if (_irrecv.decode()) {
    unitSpeedy.setIRRemoteData(_irrecv.decodedIRData.protocol,_irrecv.decodedIRData.address,_irrecv.decodedIRData.command);
    _irrecv.resume();
  }
  unitSpeedy.processingLoop();
}
