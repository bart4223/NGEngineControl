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

#define WIRELESSREMOTEDELAY    100

#define WIRELESSREMOTERIGHTPINUP    22
#define WIRELESSREMOTERIGHTPINDOWN  24
#define WIRELESSREMOTERIGHTPINLEFT  26
#define WIRELESSREMOTERIGHTPINRIGHT 28

#define STEERINGPIN       8
#define STEERINGZEROPOS   90
#define STEERINGMIN       80
#define STEERINGMAX       100
#define STEERINGSTEPWIDTH 1

#define SPEEDEASY   50

NGSimpleWirelessReceiver swrRight = NGSimpleWirelessReceiver();
NGCarSteeringControl *csc = new NGCarSteeringControl(STEERINGPIN, STEERINGZEROPOS, STEERINGMIN, STEERINGMAX, STEERINGSTEPWIDTH);
NGSimpleMotionControl *smc = new NGSimpleMotionControl(csc);
NGMotionUnitControl unitSpeedy = NGMotionUnitControl(MOTION, smc);
NGOLEDNotification *oledNotification;
#if (PROD == false)
NGSerialNotification notificationSerial = NGSerialNotification();
#endif
NGJingleBoot jingleBoot = NGJingleBoot();

void setup() {
  char log[100];
  setGlobalUnit(&unitSpeedy);
  swrRight.registerCommand(WIRELESSREMOTERIGHTPINUP, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_UP, WIRELESSREMOTEDELAY);
  swrRight.registerCommand(WIRELESSREMOTERIGHTPINDOWN, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_DOWN, WIRELESSREMOTEDELAY);
  swrRight.registerCommand(WIRELESSREMOTERIGHTPINLEFT, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_LEFT, WIRELESSREMOTEDELAY);
  swrRight.registerCommand(WIRELESSREMOTERIGHTPINRIGHT, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_RIGHT, WIRELESSREMOTEDELAY);
  swrRight.initialize();
  oledNotification = new NGOLEDNotification(OLEDTYPE, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  unitSpeedy.registerNotification(oledNotification);
  #if (PROD == false)
  unitSpeedy.registerNotification(&notificationSerial);
  #endif
  unitSpeedy.registerBoot(&jingleBoot);
  unitSpeedy.registerIRRemoteFunction(ftUp, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_UP);
  unitSpeedy.registerIRRemoteFunction(ftDown, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_DOWN);
  unitSpeedy.registerIRRemoteFunction(ftLeft, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_LEFT);
  unitSpeedy.registerIRRemoteFunction(ftRight, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_RIGHT);
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
  swrRight.processingLoop();
  if (swrRight.isCommandReceived()) {
    unitSpeedy.setIRRemoteData(swrRight.getReceivedCommandProtocol(), swrRight.getReceivedCommandAddress(), swrRight.getReceivedCommand());
  }
  unitSpeedy.processingLoop();
}
