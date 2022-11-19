#define PROD true //false,true

#include <NGSerialNotification.h>
#include <NGSimpleKeypad.h>
#include <NGSoundMachine.h>
#include <NGJingleJingleBells.h>
#include <NGBinaryClockUnitControl.h>

#define _BINARYCLOCK  "Clock"
#define BINARYCLOCK   (char*)_BINARYCLOCK

#define MODE_CLOCK 0x00
#define MODE_TREE  0x01
#define MODE_SNOW  0x02
#define MODE_FIRE  0x03
#define MODE_HEART 0x04
#define MODE_DISCO 0x05

#define KEYDELAY 500

#define KEYCOLOROFFPIN  8
#define KEYCOLOROFFID   1
#define KEYCOLORONPIN   9
#define KEYCOLORONID    2
#define KEYTREEPIN     10
#define KEYTREEID       3
#define KEYHEARTPIN    11
#define KEYHEARTID      4
#define KEYSOUNDPIN    12
#define KEYSOUNDID      5

#define HEARTBEATBASE  0x02
#define HEARTBEATRANGE 0x20

#define TREEDELAY 200
#define SNOWDELAY 250
#define FIREDELAY 100
#define HEARTDELAY 20
#define DISCODELAY 20

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

byte treeGreen[][2] = {{2, 1}, {3, 1}, {5, 1},
  {1, 2}, {2, 2}, {4, 2}, {5, 2}, {6, 2},
  {1, 3}, {2, 3}, {3, 3}, {4, 3}, {6, 3},
  {2, 4}, {4, 4}, {5, 4},
  {1, 5}, {3, 5}, {5, 5}, {6, 5},
  {1, 6}, {2, 6}, {5, 6}, {6, 6}
};

byte treeFlash[][2] = {{4, 1}, {3, 2}, {5, 3}, {3, 4}, {2, 5}, {4, 5}};
byte treeRed[][2] = {{0, 3}, {7, 3}, {0, 6}, {7, 6}};
byte treeYellow[][2] = {{3, 0}, {4, 0}, {3, 6}, {4, 6}, {3, 7}, {4, 7}};
byte treeFlashColor[7][3] = {{255, 0, 0},
  {255, 102, 0},
  {255, 255, 0},
  {0, 255, 0},
  {0, 128, 128},
  {0, 0, 255},
  {128, 0, 128}
};
long lastTree = 0;
byte treeFlashIndex = 0;

byte snow[8] = {0, 0, 0, 0, 0, 0, 0, 0};

long lastSnow = 0;

byte firePosition[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
byte fireRadius[8] = {0, 0, 0, 0, 0, 0, 0, 0};
byte fireColor[8] = {0, 0, 0, 0, 0, 0, 0, 0};
long lastFire = 0;

byte bell[][2] = {{3, 0}, {4, 0},
  {2, 1}, {3, 1}, {4, 1}, {5, 1},
  {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2},
  {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3},
  {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4},
  {0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}, {7, 5},
  {2, 6}, {3, 6}, {4, 6}, {5, 6},
  {3, 7}, {4, 7}
};

colorRGB heartColor;
byte heartBeat = HEARTBEATBASE;
bool heartDirectionUp = true;

long lastDisco = 0;

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
  simpleKeypad.registerKey(KEYTREEPIN, KEYTREEID, KEYDELAY);
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
    case MODE_TREE:
      if ((millis() - lastTree) > TREEDELAY ) {
        renderTree();
        lastTree = millis();
      }
      break;
    case MODE_SNOW:
      if ((millis() - lastSnow) > SNOWDELAY ) {
        renderSnow();
        lastSnow = millis();
      }
      break;
    case MODE_FIRE:
      if ((millis() - lastFire) > FIREDELAY ) {
        renderFire();
        lastFire = millis();
      }
      break;
    case MODE_HEART:
      renderHeart();
      break;
    case MODE_DISCO:
      if ((millis() - lastDisco) > DISCODELAY ) {
        renderDisco();
        lastDisco = millis();
      }
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
    case KEYTREEID:
      switch(mode) {
        case MODE_CLOCK:
        case MODE_HEART:
        case MODE_DISCO:
          mode = MODE_TREE;
          break;
        case MODE_TREE:
          mode = MODE_SNOW;
          for (int i = 0; i < sizeof(snow) / sizeof(snow[0]); i++) {
            snow[i] = 0;
          }
          break;
        case MODE_SNOW:
          mode = MODE_FIRE;
          for (int i = 0; i < sizeof(firePosition) / sizeof(firePosition[0]); i++) {
            firePosition[i] = 0xFF;
            fireRadius[i] = 0;
            fireColor[i] = 0;
          }
          break;
        case MODE_FIRE:
          cdm.clear();
          mode = MODE_CLOCK;
          break;
      }
      break;
    case KEYHEARTID:
      switch(mode) {
        case MODE_CLOCK:
        case MODE_TREE:
        case MODE_SNOW:
        case MODE_FIRE:
          mode = MODE_HEART;
          break;
        case MODE_HEART:
          mode = MODE_DISCO;
          break;
        case MODE_DISCO:
          cdm.clear();
          mode = MODE_CLOCK;
          break;
      }
      break;
    case KEYSOUNDID:
      cdm.clear();
      cdm.drawImage(bell, COLOR_RED, sizeof(bell) / sizeof(bell[0]));
      sm.play(0);
      cdm.clear();
      break;
    default:
      Serial.println(id);
      break;
  }
}

void renderFire() {
  cdm.beginUpdate();
  cdm.clear();
  colorRGB c;
  for (int i = 0; i < sizeof(firePosition) / sizeof(firePosition[0]); i++) {
    if (firePosition[i] == 0xFF) {
      if (random(0, 20) == 10) {
        firePosition[i] = random(0, 7);
        fireRadius[i] = 0;
        fireColor[i] = random(0, 7);
      }
    }
    if (firePosition[i] != 0xFF) {
      c.red = treeFlashColor[fireColor[i]][0];
      c.green = treeFlashColor[fireColor[i]][1];
      c.blue = treeFlashColor[fireColor[i]][2];
      cdm.drawCircle(i, firePosition[i], fireRadius[i], c);
      fireRadius[i]++;
      if (fireRadius[i] > 8) {
        firePosition[i] = 0xFF;
        fireRadius[i] = 0;
        fireColor[i] = 0;
      }
    }
  }
  cdm.endUpdate();
}

void renderSnow() {
  cdm.beginUpdate();
  cdm.clear();
  for (int i = 0; i < sizeof(snow) / sizeof(snow[0]); i++) {
    if (random(0, 10) == 5) {
      if ((snow[i] & 0x02) == 0x00) {
        snow[i] = snow[i] | 0x01;
      }
    }
    colorRGB c;
    byte x = 0x01;
    for (int j = 0; j < 7; j++) {
      if ((snow[i] & x) != 0x00) {
        c.red = 50 + random(0, 100);
        c.green = 100 + random(0, 100);
        c.blue = 100 + random(0, 150);
        cdm.drawPoint(i, j, c);
      }
      x = x << 1;
    }
    snow[i] = snow[i] << 1;
  }
  cdm.drawLine(0, 7, 7, 7, COLOR_WHITE);
  cdm.endUpdate();
}

void renderTree() {
  cdm.beginUpdate();
  cdm.clear();
  cdm.drawImage(treeGreen, COLOR_GREEN, sizeof(treeGreen) / sizeof(treeGreen[0]));
  cdm.drawImage(treeRed, COLOR_RED, sizeof(treeRed) / sizeof(treeRed[0]));
  cdm.drawImage(treeYellow, COLOR_YELLOW, sizeof(treeYellow) / sizeof(treeYellow[0]));
  colorRGB c;
  for (int i = 0; i < sizeof(treeFlash) / sizeof(treeFlash[0]); i++) {
    c.red = treeFlashColor[treeFlashIndex][0];
    c.green = treeFlashColor[treeFlashIndex][1];
    c.blue = treeFlashColor[treeFlashIndex][2];
    cdm.drawPoint(treeFlash[i][0], treeFlash[i][1], c);
    treeFlashIndex++;
    if (treeFlashIndex >= 7) {
      treeFlashIndex = 0;
    }
  }
  cdm.endUpdate();
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

void renderDisco() {
  cdm.beginUpdate();
  colorRGB c;
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y <8; y++) {
      c.red = random(0, 256);
      c.green = random(0, 256);
      c.blue = random(0, 256);
      cdm.drawPoint(x, y, c);
    }
  }
  cdm.endUpdate();
}
