#define PROD false //false,true

#include <NGAnchormanUnitControl.h>
#if (PROD == false)
#include <NGSerialNotification.h>
#endif
#include <NGOLEDNotification.h>
#include <NGJingleBoot.h>
#include <NGJingleBeep.h>

#define _ANCHORMNAN "Anchorman"
#define ANCHORMNAN  (char*)_ANCHORMNAN

#define OLEDADDRESS       0x3C
#define OLEDCOLUMNS       16
#define OLEDTYPE          ot128x32
#define OLEDLINES         4
#define OLEDLINEFACTOR    2

#define TURNTABLESPEED         128
#define TURNTABLEDELAY         125
#define MOTIONPROFILERUNFORWARD    250
#define MOTIONPROFILERUNBACKWARD   250
#define MOTIONPROFILESTOP        60000

NGAnchormanUnitControl unitAnchorman = NGAnchormanUnitControl(ANCHORMNAN);
#if (PROD == false)
NGSerialNotification serialNotification = NGSerialNotification();
#endif
NGOLEDNotification *oledNotification;

void setup() {
  setGlobalUnit(&unitAnchorman);
  #if (PROD != true)
  unitAnchorman.registerNotification(&serialNotification);
  #else
  unitAnchorman.setLogging(false);
  #endif
  oledNotification = new NGOLEDNotification(OLEDTYPE, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  unitAnchorman.registerNotification(oledNotification);
  unitAnchorman.registerBoot(new NGJingleBoot);
  unitAnchorman.registerBeep(new NGJingleBeep);
  int ttmp = unitAnchorman.registerSimpleTurnTableMotionProfile(MOTIONPROFILERUNFORWARD, MOTIONPROFILESTOP, MOTIONPROFILERUNBACKWARD, MOTIONPROFILESTOP);
  unitAnchorman.registerTurnTable(new NGEngineControl(ENGINE_0), TURNTABLESPEED, TURNTABLEDELAY, ttmp);
  unitAnchorman.initialize();
  #if (PROD == true)
  unitAnchorman.setWorkMode(wmNone);
  #else
  unitAnchorman.setWorkMode(wmObserveMemory);
  #endif
  unitAnchorman.startUp();
  unitAnchorman.clearInfo();
}

void loop() {
  unitAnchorman.processingLoop();
}
