#define PROD true //false,true

#include <NGSerialNotification.h>
#include <NGSimpleKeypad.h>
#include <NGSoundMachine.h>
#include <NGJingleJingleBells.h>
#include <NGBinaryClockUnitControl.h>

#define _BINARYCLOCK  "Clock"
#define BINARYCLOCK   (char*)_BINARYCLOCK

#define MODE_CLOCK 0x00
#define MODE_HEART 0x01

#define KEYDELAY 500

#define KEYCOLOROFFPIN  8
#define KEYCOLOROFFID   1
#define KEYCOLORONPIN   9
#define KEYCOLORONID    2
#define KEY3PIN   10
#define KEY3ID    3
#define KEYHEARTPIN    11
#define KEYHEARTID      4
#define KEYSOUNDPIN    12
#define KEYSOUNDID      5

#define HEARTBEATBASE  0x02
#define HEARTBEATRANGE 0x20

#define HEARTDELAY 20

NGSoundMachine sm = NGSoundMachine();
NGSimpleKeypad simpleKeypad = NGSimpleKeypad();
NGColorDotMatrix cdm = NGColorDotMatrix();
NGBinaryClockUnitControl unitBinaryClock = NGBinaryClockUnitControl(BINARYCLOCK, &cdm);
#if (PROD == false)
NGSerialNotification serialNotification = NGSerialNotification();
#endif

byte heart[][2] = {
  {1, 1}, {2, 1}, {5, 1}, {6, 1},
  {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2},
  {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3},
  {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4},
  {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5},
  {2, 6}, {3, 6}, {4, 6}, {5, 6},
  {3, 7}, {4, 7}
};

colorRGB heartColor;
byte heartBeat = HEARTBEATBASE;
bool heartDirectionUp = true;

colorRGB colorOff = COLOR_LIME;
colorRGB colorOn = COLOR_BLUE;

byte mode = MODE_CLOCK;

void setup() {
  setGlobalUnit(&unitBinaryClock);
  #if (PROD == false)
  unitBinaryClock.registerNotification(&serialNotification);
  #endif
  unitBinaryClock.setColorOff(colorOff);
  unitBinaryClock.setColorOn(colorOn);
  unitBinaryClock.initialize();
  simpleKeypad.registerCallback(&SimpleKeypadCallback);
  simpleKeypad.registerKey(KEYCOLOROFFPIN, KEYCOLOROFFID, KEYDELAY);
  simpleKeypad.registerKey(KEYCOLORONPIN, KEYCOLORONID, KEYDELAY);
  simpleKeypad.registerKey(KEY3PIN, KEY3ID, KEYDELAY);
  simpleKeypad.registerKey(KEYHEARTPIN, KEYHEARTID, KEYDELAY);
  simpleKeypad.registerKey(KEYSOUNDPIN, KEYSOUNDID, KEYDELAY);
  simpleKeypad.initialize();
  sm.registerJingle(new NGJingleJingleBells);
  sm.initialize();
  #if (PROD == true)
  unitBinaryClock.setWorkMode(wmNone);
  #else
  unitBinaryClock.setWorkMode(wmObserveMemory);
  #endif
  unitBinaryClock.startUp();
  unitBinaryClock.clearInfo();
}

void loop() {
  simpleKeypad.processingLoop();
  switch(mode) {
    case MODE_CLOCK:
      unitBinaryClock.processingLoop();
      break;
    case MODE_HEART:
      renderHeart();
      break;
  }
}

void SimpleKeypadCallback(byte id) {
  switch(id) {
    case KEYCOLOROFFID:
      if (mode != MODE_CLOCK) {
        cdm.clear();
        mode = MODE_CLOCK;
      } else {
        colorOff.red = random(0, 256);
        colorOff.green = random(0, 256);
        colorOff.blue = random(0, 256);
        unitBinaryClock.setColorOff(colorOff);
      }
      break;
    case KEYCOLORONID:
      if (mode != MODE_CLOCK) {
        cdm.clear();
        mode = MODE_CLOCK;
      } else {
        mode = MODE_CLOCK;
        colorOn.red = random(0, 256);
        colorOn.green = random(0, 256);
        colorOn.blue = random(0, 256);
        unitBinaryClock.setColorOn(colorOn);
      }
      break;
    case KEYHEARTID:
      if (mode != MODE_HEART) {
        mode = MODE_HEART;
      } else {
        cdm.clear();
        mode = MODE_CLOCK;
      }
      break;
    case KEYSOUNDID:
      sm.play(0);
      break;
    default:
      Serial.println(id);
      break;
  }
}

void renderHeart() {
  cdm.beginUpdate();
  cdm.clear();
  heartColor.red = heartBeat;
  cdm.drawImage(heart, heartColor, sizeof(heart) / sizeof(heart[0]));
  cdm.endUpdate();
  delay(HEARTDELAY);
  if (heartDirectionUp) {
    if (heartBeat == HEARTBEATRANGE + HEARTBEATBASE) {
      heartBeat--;
      heartDirectionUp = false;
    } else {
      heartBeat++;
    }
  } else {
    if (heartBeat == HEARTBEATBASE) {
      heartBeat++;
      heartDirectionUp = true;
    } else {
      heartBeat--;
    }
  }
}
