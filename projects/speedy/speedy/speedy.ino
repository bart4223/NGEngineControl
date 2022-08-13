#define PROD false  //false,true

#include <NGSimpleWirelessReceiver.h>
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

#define QIACHIPDELAY 500
#define QIACHIPPINUP 7

#define SPEEDEASY   50

NGSimpleWirelessReceiver swr = NGSimpleWirelessReceiver();
NGMotionUnitControl unitSpeedy = NGMotionUnitControl(MOTION, new NGSimpleMotionControl(new NGCarSteeringControl()));
NGOLEDNotification *oledNotification;
#if (PROD == false)
NGSerialNotification notificationSerial = NGSerialNotification();
#endif

void setup() {
  setGlobalUnit(&unitSpeedy);
  swr.registerCommand(QIACHIPPINUP, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_UP, QIACHIPDELAY);
  swr.initialize();
  oledNotification = new NGOLEDNotification(OLEDTYPE, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  unitSpeedy.registerNotification(oledNotification);
  #if (PROD == false)
  unitSpeedy.registerNotification(&notificationSerial);
  #endif
  unitSpeedy.registerIRRemoteFunction(ftUp, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_UP);
  DEF_MOTION_SEQUENCE_START;
  // forward
  DEF_MOTION_SEQUENCE_BEGIN_STRAIGHT(unitSpeedy);
  DEF_MOTION_SEQUENCE_FORWARD(unitSpeedy, SPEEDEASY, 0);
  DEF_MOTION_SEQUENCE_END_STRAIGHT;
  // stop
  DEF_MOTION_SEQUENCE_BEGIN_STOP(unitSpeedy);
  DEF_MOTION_SEQUENCE_STOP(unitSpeedy, 0);
  DEF_MOTION_SEQUENCE_END_STOP;
  unitSpeedy.initialize();
  #if (PROD == false)
  unitSpeedy.setWorkMode(wmObserveMemory);
  #endif
  unitSpeedy.startUp();
  unitSpeedy.clearInfo();
}

void loop() {
  swr.processingLoop();
  if (swr.isCommandReceived()) {
    unitSpeedy.setIRRemoteData(swr.getReceivedCommandProtocol(), swr.getReceivedCommandAddress(), swr.getReceivedCommand());
  }
  unitSpeedy.processingLoop();
}
