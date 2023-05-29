#define PROD true //false,true

#include <NGSimpleWirelessReceiver.h>
#include <NGMotionUnitControl.h>
#include <NGRemoteMotionControl.h>
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

#define PINLIGHTSENSOR    A0
#define PINLIGHT           4

#define WIRELESSREMOTEDELAYUP      300
#define WIRELESSREMOTEDELAYDOWN    300
#define WIRELESSREMOTEDELAYLEFT     30
#define WIRELESSREMOTEDELAYRIGHT    30

#define WIRELESSREMOTERIGHT         0x01
#define WIRELESSREMOTERIGHTPINUP    24
#define WIRELESSREMOTERIGHTPINDOWN  26
#define WIRELESSREMOTERIGHTPINLEFT  28
#define WIRELESSREMOTERIGHTPINRIGHT 30

#define WIRELESSREMOTELEFT          0x02
#define WIRELESSREMOTELEFTPINUP     25
#define WIRELESSREMOTELEFTPINDOWN   27
#define WIRELESSREMOTELEFTPINLEFT   29
#define WIRELESSREMOTELEFTPINRIGHT  31

#define STEERINGPIN         8
#define STEERINGZEROPOS    96
#define STEERINGMIN        66
#define STEERINGMAX       126
#define STEERINGSTEPWIDTH   2

#define SPEEDFORWARD1    50
#define SPEEDFORWARD2   100
#define SPEEDFORWARD3   150
#define SPEEDFORWARD4   200
#define SPEEDBACKWARD1   50
#define SPEEDBACKWARD2  100
#define SPEEDCURVE        0

#define LIGHTSENSORDELAY      1000
#define LIGHTSENSORTHRESHOLD   650

NGSimpleWirelessReceiver swrRight = NGSimpleWirelessReceiver(WIRELESSREMOTERIGHT);
NGSimpleWirelessReceiver swrLeft = NGSimpleWirelessReceiver(WIRELESSREMOTELEFT);
NGLightSensor lightSensor = NGLightSensor(PINLIGHTSENSOR);
NGCarSteeringControl *csc = new NGCarSteeringControl(STEERINGPIN, STEERINGZEROPOS, STEERINGMIN, STEERINGMAX, STEERINGSTEPWIDTH);
NGRemoteMotionControl *rmc = new NGRemoteMotionControl(csc);
NGMotionUnitControl unitSpeedy = NGMotionUnitControl(MOTION, rmc);
NGOLEDNotification *oledNotification;
#if (PROD == false)
NGSerialNotification notificationSerial = NGSerialNotification();
#endif
NGJingleBoot jingleBoot = NGJingleBoot();

void setup() {
  char log[100];
  setGlobalUnit(&unitSpeedy);
  swrRight.registerCommand(WIRELESSREMOTERIGHTPINUP, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_UP, WIRELESSREMOTEDELAYUP);
  swrRight.registerCommand(WIRELESSREMOTERIGHTPINDOWN, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_DOWN, WIRELESSREMOTEDELAYDOWN);
  swrRight.registerCommand(WIRELESSREMOTERIGHTPINLEFT, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_LEFT, WIRELESSREMOTEDELAYLEFT);
  swrRight.registerCommand(WIRELESSREMOTERIGHTPINRIGHT, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_RIGHT, WIRELESSREMOTEDELAYRIGHT);
  swrRight.initialize();
  swrLeft.registerCommand(WIRELESSREMOTELEFTPINUP, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_UP, WIRELESSREMOTEDELAYUP);
  swrLeft.initialize();
  oledNotification = new NGOLEDNotification(OLEDTYPE, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  unitSpeedy.registerNotification(oledNotification);
  #if (PROD == false)
  unitSpeedy.registerNotification(&notificationSerial);
  #else
  unitSpeedy.setLogging(false);
  #endif
  unitSpeedy.registerBoot(&jingleBoot);
  unitSpeedy.registerLightSensor(&lightSensor, LIGHTSENSORTHRESHOLD, tlUnder, PINLIGHT, tvHigh, LIGHTSENSORDELAY);
  // Joystick left
  unitSpeedy.registerIRRemoteFunction(swrLeft.getID(), ftPlay, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_UP);
  // Joystick right
  unitSpeedy.registerIRRemoteFunction(swrRight.getID(), ftUp, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_UP);
  unitSpeedy.registerIRRemoteFunction(swrRight.getID(), ftDown, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_DOWN);
  unitSpeedy.registerIRRemoteFunction(swrRight.getID(), ftLeft, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_LEFT);
  unitSpeedy.registerIRRemoteFunction(swrRight.getID(), ftRight, IRP_QIACHIP, IRA_QIACHIP, IRC_QIACHIP_RIGHT);
  DEF_MOTION_SEQUENCE_START;
  // stop
  DEF_MOTION_SEQUENCE_BEGIN_STOP(unitSpeedy);
  DEF_MOTION_SEQUENCE_STOP(unitSpeedy, 0);
  DEF_MOTION_SEQUENCE_END_STOP;
  // forward 1
  DEF_MOTION_SEQUENCE_BEGIN_STRAIGHT(unitSpeedy);
  DEF_MOTION_SEQUENCE_FORWARD(unitSpeedy, SPEEDFORWARD1, 0);
  DEF_MOTION_SEQUENCE_END_STRAIGHT;
  // forward 2
  DEF_MOTION_SEQUENCE_BEGIN_STRAIGHT(unitSpeedy);
  DEF_MOTION_SEQUENCE_FORWARD(unitSpeedy, SPEEDFORWARD2, 0);
  DEF_MOTION_SEQUENCE_END_STRAIGHT;
  // forward 3
  DEF_MOTION_SEQUENCE_BEGIN_STRAIGHT(unitSpeedy);
  DEF_MOTION_SEQUENCE_FORWARD(unitSpeedy, SPEEDFORWARD3, 0);
  DEF_MOTION_SEQUENCE_END_STRAIGHT;
  // forward 4
  DEF_MOTION_SEQUENCE_BEGIN_STRAIGHT(unitSpeedy);
  DEF_MOTION_SEQUENCE_FORWARD(unitSpeedy, SPEEDFORWARD4, 0);
  DEF_MOTION_SEQUENCE_END_STRAIGHT;
  // backward 1
  DEF_MOTION_SEQUENCE_BEGIN_BACK(unitSpeedy);
  DEF_MOTION_SEQUENCE_BACKWARD(unitSpeedy, SPEEDBACKWARD1, 0);
  DEF_MOTION_SEQUENCE_END_BACK;
  // backward 2
  DEF_MOTION_SEQUENCE_BEGIN_BACK(unitSpeedy);
  DEF_MOTION_SEQUENCE_BACKWARD(unitSpeedy, SPEEDBACKWARD2, 0);
  DEF_MOTION_SEQUENCE_END_BACK;
  // left
  DEF_MOTION_SEQUENCE_BEGIN_LEFT(unitSpeedy);
  DEF_MOTION_SEQUENCE_FORWARD_ONLY_LEFT(unitSpeedy, SPEEDCURVE, 1);
  DEF_MOTION_SEQUENCE_END_LEFT;
  // right
  DEF_MOTION_SEQUENCE_BEGIN_RIGHT(unitSpeedy);
  DEF_MOTION_SEQUENCE_FORWARD_ONLY_RIGHT(unitSpeedy, SPEEDCURVE, 1);
  DEF_MOTION_SEQUENCE_END_RIGHT;
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
    unitSpeedy.setIRRemoteData(swrRight.getID(), swrRight.getReceivedCommandProtocol(), swrRight.getReceivedCommandAddress(), swrRight.getReceivedCommand());
  }
  swrLeft.processingLoop();
  if (swrLeft.isCommandReceived()) {
    unitSpeedy.setIRRemoteData(swrLeft.getID(), swrLeft.getReceivedCommandProtocol(), swrLeft.getReceivedCommandAddress(), swrLeft.getReceivedCommand());
  }
  unitSpeedy.processingLoop();
}
