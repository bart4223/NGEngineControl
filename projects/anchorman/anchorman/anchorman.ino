#define PROD true //false,true

#include <NGAnchormanUnitControl.h>
#include <NGSimpleKeypad.h>
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

#define KEYMODEPIN    2
#define KEYDOWNPIN    3
#define KEYUPPIN      4
#define KEYMODEID    10
#define KEYMODEDOWN  11
#define KEYMODEUP    12
#define KEYPADDELAY 500
#define KEYPADUSAGEDELAY 5000

#define STEPSGO        10
#define STEPSWAIT   10000

NGAnchormanUnitControl unitAnchorman = NGAnchormanUnitControl(ANCHORMNAN);
NGSimpleKeypad keypad = NGSimpleKeypad();
#if (PROD == false)
NGSerialNotification serialNotification = NGSerialNotification();
#endif
NGOLEDNotification *oledNotification;
byte mode = 0;
int profile = -1;
long lastKeyPadUsage;

void setup() {
  setGlobalUnit(&unitAnchorman);
  #if (PROD != true)
  unitAnchorman.registerNotification(&serialNotification);
  #else
  unitAnchorman.setLogging(false);
  #endif
  oledNotification = new NGOLEDNotification(OLEDTYPE, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  unitAnchorman.registerNotification(oledNotification);
  #if (PROD == false)
  unitAnchorman.registerBoot(new NGJingleBoot);
  #endif
  unitAnchorman.registerBeep(new NGJingleBeep);
  profile = unitAnchorman.registerSimpleTurnTableMotionProfile(MOTIONPROFILERUNFORWARD, MOTIONPROFILESTOP, MOTIONPROFILERUNBACKWARD, MOTIONPROFILESTOP);
  unitAnchorman.registerTurnTable(new NGEngineControl(ENGINE_2), TURNTABLESPEED, TURNTABLEDELAY, profile);
  unitAnchorman.initialize();
  keypad.registerCallback(&KeypadCallback);
  keypad.registerKey(KEYMODEPIN, KEYMODEID, KEYPADDELAY);
  keypad.registerKey(KEYUPPIN, KEYMODEUP, KEYPADDELAY);
  keypad.registerKey(KEYDOWNPIN, KEYMODEDOWN, KEYPADDELAY);
  keypad.initialize();
  #if (PROD == true)
  unitAnchorman.setWorkMode(wmNone);
  #else
  unitAnchorman.setWorkMode(wmObserveMemory);
  #endif
  unitAnchorman.startUp();
  unitAnchorman.clearInfo();
}

void loop() {
  checkKeyPadUsage();
  keypad.processingLoop();
  unitAnchorman.processingLoop();
}

void checkKeyPadUsage() {
  if (lastKeyPadUsage != 0) {
    if (millis() - lastKeyPadUsage > KEYPADUSAGEDELAY) {
      mode = 0;
      lastKeyPadUsage = 0;
      unitAnchorman.clearInfo();
    }
  }
}

void KeypadCallback(byte id) {
  #if (PROD == true)
  unitAnchorman.beep();
  #endif
  lastKeyPadUsage = millis();
  char log[100];
  byte step;
  switch(id) {
    case KEYMODEID:
      mode++;
      if (mode == 5) {
        mode = 1;
      }
      switch(mode) {
        case 1:
          step = 0;
          break;
        case 2:
          step = 1;
          break;
        case 3:
          step = 2;
          break;
        case 4:
          step = 3;
          break;
      }
      break;
    case KEYMODEDOWN:
      switch(mode) {
        case 1:
          step = 0;
          if (unitAnchorman.getMotionProfileStep(profile, step) > STEPSGO) {
            unitAnchorman.decrementMotionProfileStep(profile, step, STEPSGO);
          }
          break;
        case 2:
          step = 1;
          if (unitAnchorman.getMotionProfileStep(profile, step) > STEPSWAIT) {
            unitAnchorman.decrementMotionProfileStep(profile, step, STEPSWAIT);
          }
          break;
        case 3:
          step = 2;
          if (unitAnchorman.getMotionProfileStep(profile, step) > STEPSGO) {
            unitAnchorman.decrementMotionProfileStep(profile, step, STEPSGO);
          }
          break;
        case 4:
          step = 3;
          if (unitAnchorman.getMotionProfileStep(profile, step) > STEPSWAIT) {
            unitAnchorman.decrementMotionProfileStep(profile, step, STEPSWAIT);
          }
          break;
      }
      break;
    case KEYMODEUP:
      switch(mode) {
        case 1:
          step = 0;
          unitAnchorman.incrementMotionProfileStep(profile, step, STEPSGO);
          break;
        case 2:
          step = 1;
          unitAnchorman.incrementMotionProfileStep(profile, step, STEPSWAIT);
          break;
        case 3:
          step = 2;
          unitAnchorman.incrementMotionProfileStep(profile, step, STEPSGO);
          break;
        case 4:
          step = 3;
          unitAnchorman.incrementMotionProfileStep(profile, step, STEPSWAIT);
          break;
      }
      break;
  }
  unitAnchorman.clearInfo();
  sprintf(log, "P%d S%d: %ld", profile, step, unitAnchorman.getMotionProfileStep(profile, step));
  unitAnchorman.writeInfo(log);
}
