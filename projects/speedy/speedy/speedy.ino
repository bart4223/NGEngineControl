#define PROD false //false,true

#include <NGSimpleWirelessReceiver.h>
#include <NGMotionUnitControl.h>
#include <NGSimpleMotionControl.h>
#include <NGCarSteeringControl.h>
#include <NGOLEDNotification.h>
#if (PROD == false)
#include <NGSerialNotification.h>
#endif
#include <NGMotionSequenceDefinitions.h>
#include <NGJingleBoot.h>

#define _MOTION  "Speedy"
#define MOTION    (char*)_MOTION

#define OLEDADDRESS       0x3C
#define OLEDCOLUMNS       16
#define OLEDTYPE          ot128x64
#define OLEDLINES         8
#define OLEDLINEFACTOR    4

#define QIACHIPDELAY    100
#define QIACHIPPINUP    22
#define QIACHIPPINDOWN  24

#define SPEEDEASY   50

NGSimpleWirelessReceiver swr = NGSimpleWirelessReceiver();
NGMotionUnitControl unitSpeedy = NGMotionUnitControl(MOTION, new NGSimpleMotionControl(new NGCarSteeringControl()));
NGOLEDNotification *oledNotification;
#if (PROD == false)
NGSerialNotification notificationSerial = NGSerialNotification();
#endif
NGJingleBoot jingleBoot = NGJingleBoot();

void setup() {
  char log[100];
  setGlobalUnit(&unitSpeedy);
  swr.registerCommand(QIACHIPPINUP, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_UP, QIACHIPDELAY);
  swr.registerCommand(QIACHIPPINDOWN, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_DOWN, QIACHIPDELAY);
  swr.initialize();
  oledNotification = new NGOLEDNotification(OLEDTYPE, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  unitSpeedy.registerNotification(oledNotification);
  #if (PROD == false)
  unitSpeedy.registerNotification(&notificationSerial);
  #endif
  unitSpeedy.registerBoot(&jingleBoot);
  unitSpeedy.registerIRRemoteFunction(ftUp, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_UP);
  unitSpeedy.registerIRRemoteFunction(ftDown, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_DOWN);
  DEF_MOTION_SEQUENCE_START;
  // stop
  DEF_MOTION_SEQUENCE_BEGIN_STOP(unitSpeedy);
  DEF_MOTION_SEQUENCE_STOP(unitSpeedy, 0);
  DEF_MOTION_SEQUENCE_END_STOP;
  // forward
  DEF_MOTION_SEQUENCE_BEGIN_STRAIGHT(unitSpeedy);
  DEF_MOTION_SEQUENCE_FORWARD(unitSpeedy, SPEEDEASY, 0);
  DEF_MOTION_SEQUENCE_END_STRAIGHT;
  // backward
  DEF_MOTION_SEQUENCE_BEGIN_BACK(unitSpeedy);
  DEF_MOTION_SEQUENCE_BACKWARD(unitSpeedy, SPEEDEASY, 0);
  DEF_MOTION_SEQUENCE_END_BACK;
  unitSpeedy.initialize();
  #if (PROD == false)
  unitSpeedy.setWorkMode(wmObserveMemory);
  #endif
  unitSpeedy.startUp();
  unitSpeedy.clearInfo();
  sprintf(log, "Lets go...");
  unitSpeedy.writeInfo(log);
}

void loop() {
  swr.processingLoop();
  if (swr.isCommandReceived()) {
    unitSpeedy.setIRRemoteData(swr.getReceivedCommandProtocol(), swr.getReceivedCommandAddress(), swr.getReceivedCommand());
  }
  unitSpeedy.processingLoop();
}
