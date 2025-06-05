#define LEDSTRIPCIRCLE7 //LEDSTRIP8, LEDSTRIP100, LEDSTRIP256, LEDSTRIPAUTO, LEDSTRIPCIRCLE7
#define TESTMODEDEFAULT //TESTMODEDEFAULT, TESTMODEPIXEL
#define WITHOUTBEEP //WITHOUTBEEP, WITHBEEP 
#define ARDUINO_NANO //ARDUINO_MEGA, ARDUINO_NANO
#define WITHOUTLCD //WITHLCD, WITHOUTLCD

#include <NGEngineCore.h>
#include <NGColorLEDStrip.h>
#ifdef WITHBEEP
#include <NGSoundMachine.h>
#include <NGJingleBoot.h>
#include <NGJingleBeep.h>
#include <NGJingleAlarm.h>
#include <NGDigitalPotentiometer.h>
#endif
#ifdef WITHLCD
#include <NGLCDNotification.h>
#endif

#define PINLED                8
#define PINAUTODETECTIONLED  A0
#ifdef WITHLCD
#define PINAUTODETECTIONLCD  A1
#define LCD_INDICATOR       900
#endif

#define LEDSTRIP8_PIXELS         8
#define LEDSTRIP8_ROWS           1
#define LEDSTRIP100_INDICATOR  900
#define LEDSTRIP100_PIXELS     100
#define LEDSTRIP100_ROWS        10
#define LEDSTRIP256_INDICATOR  800
#define LEDSTRIP256_PIXELS     256
#define LEDSTRIP256_ROWS        16
#define LEDSTRIPCIRCLE7_PIXELS 113
#define LEDSTRIPCIRCLE7_RADIUS   7
//Radius 1  1
//Radius 2  8
//Radius 3 12
//Radius 4 16
//Radius 5 20
//Radius 6 24
//Radius 7 32

#define BRIGHTNESS 0.05
//#define BRIGHTNESS 0.5

#define DELAY        500
#ifdef TESTMODEPIXEL
#define TESTRUNS       1
#else
#define TESTRUNS       1
#endif
#define TESTDELAY    100
#define TESTMODEDELAY 20

#define START 0x00
#define STOP  0x05

#ifdef WITHBEEP
#define SOUNDACTIVATIONPIN 9
#define ADDRESS_POTI 0x00
#define PIN_CS 53
#define POTI_MAX 255
#define POTI_MIN 225
#define POTI_STEP  5
NGSoundMachine *sm = new NGSoundMachine(DEFPINPIEZO, SOUNDACTIVATIONPIN);
NGDigitalPotentiometer dp = NGDigitalPotentiometer(PIN_CS, ADDRESS_POTI);
#endif
#ifdef WITHLCD
#define LCDADDRESS    0x27
#define LCDCOLUMNS    16
#define LCDLINES      2
#endif

#ifdef LEDSTRIPAUTO
// 1K = 100 Pixel
// 2K = 256 Pixel
NGColorLEDStrip cls = NGColorLEDStrip(PINLED, PINAUTODETECTIONLED);
#endif
#ifdef LEDSTRIP8
NGColorLEDStrip cls = NGColorLEDStrip(PINLED, LEDSTRIP8_PIXELS, LEDSTRIP8_ROWS);
#endif
#ifdef LEDSTRIP100
NGColorLEDStrip cls = NGColorLEDStrip(PINLED, LEDSTRIP100_PIXELS, LEDSTRIP100_ROWS);
#endif
#ifdef LEDSTRIP256
NGColorLEDStrip cls = NGColorLEDStrip(PINLED, LEDSTRIP256_PIXELS, LEDSTRIP256_ROWS, lskUpDownAlternate);
#endif
#ifdef LEDSTRIPCIRCLE7
NGColorLEDStrip cls = NGColorLEDStrip(PINLED, LEDSTRIPCIRCLE7_PIXELS, 1);
#endif

#ifdef ARDUINO_MEGA
#define KEYBEEPPIN        26
#define KEYBEEPID         42
#define KEYBRIGHTNESSPIN  27
#define KEYBRIGHTNESSID   43
#else
#define KEYBEEPPIN        10
#define KEYBEEPID         42
#define KEYBRIGHTNESSPIN  11
#define KEYBRIGHTNESSID   43
#endif

#define KEYDELAY 250

NGSimpleKeypad skp = NGSimpleKeypad();

coord2D img[] = {{0, 0}, {1, 1}, {2, 2}};
colorRGB clr[] = {COLOR_RED, COLOR_GREEN, COLOR_BLUE};

#ifdef WITHLCD
NGLCDNotification *lcd;
#endif

byte step = START;
long lastUpdate = 0;

byte jingleBootID;
byte jingleBeepID;
byte jingleAlarmID;

bool hasLCD;

void setup() {
  observeMemory(0);
  initGlobalRandomSeedWithAnalogInput(A5);
  skp.registerCallback(&SimpleKeypadCallback);
  skp.registerKey(KEYBEEPPIN, KEYBEEPID, KEYDELAY);
  skp.registerKey(KEYBRIGHTNESSPIN, KEYBRIGHTNESSID, KEYDELAY);
  //cls.setLogging(true);
  cls.setIndicatorRange(49);
  cls.registerGeometry(LEDSTRIP100_INDICATOR, LEDSTRIP100_PIXELS, LEDSTRIP100_ROWS);
  cls.registerGeometry(LEDSTRIP256_INDICATOR, lskUpDownAlternate, LEDSTRIP256_PIXELS, LEDSTRIP256_ROWS);
  cls.setOffset(0, 0);
  //cls.setTestColor(COLOR_WHITE);
  #ifdef TESTMODEPIXEL
  cls.setTestMode(tmPixel);
  #endif
  cls.setTestModeDelay(TESTMODEDELAY);
  cls.initialize(BRIGHTNESS);
  for (int i = 0; i < TESTRUNS; i++) {
    cls.testSequenceStart();
    delay(TESTDELAY);
  }
  cls.testSequenceStop();
  skp.initialize();
  #ifdef WITHBEEP
  dp.setMinValue(POTI_MIN);
  dp.setMaxValue(POTI_MAX);
  dp.setStepValue(POTI_STEP);
  dp.initialize(POTI_MIN);
  sm->setConcurrently(true);
  jingleBootID = sm->registerJingle(new NGJingleBoot);
  jingleBeepID = sm->registerJingle(new NGJingleBeep);
  jingleAlarmID = sm->registerJingle(new NGJingleAlarm);
  sm->initialize();
  sm->activate();
  sm->play(jingleBootID);
  #endif
  #ifdef WITHLCD
  int lcdValue = analogRead(PINAUTODETECTIONLCD);
  hasLCD = lcdValue > LCD_INDICATOR - 100 && lcdValue < LCD_INDICATOR + 100;
  if (hasLCD) {
    lcd = new NGLCDNotification(LCDADDRESS, LCDCOLUMNS, LCDLINES);
    lcd->initialize();
    lcd->writeInfo("LED Strip", 0, 3);
    lcd->writeInfo("Test and Debug", 1, 1);
  }
  #endif
  observeMemory(0);
}

void loop() {
  skp.processingLoop();
  #ifdef WITHBEEP
  sm->processingLoop();
  #endif
  if (millis() - lastUpdate > DELAY) {
    cls.clear();
    #ifdef LEDSTRIP8
    if (step % 2 == 0) {
      colorRGB c;
      if (getYesOrNo()) {
        c = COLOR_RED;
      } else {
        c = COLOR_GREEN;
      }
      for(int i = 0; i < 8; i++) {
        cls.drawPoint(i, 0, c);
      }
    } else {
      for(int i = 0; i < 8; i++) {
        cls.drawPoint(i, 0, COLOR_BLACK);
      }      
    }
    #else
    switch (step) {
      case 0x00:
        cls.drawLine(1, 1, 8, 6, COLOR_RED);
        break;
      case 0x01:
        cls.drawRect(2, 2, 6, 7, COLOR_GREEN);
        break;
      case 0x02:
        cls.fillRect(3, 3, 6, 7, COLOR_BLUE);
        break;
      case 0x03:
        cls.drawCircle(5, 5, 2, COLOR_YELLOW);
        break;
      case 0x04:
        cls.drawImage(img, clr, sizeof(img) / sizeof(img[0]));
        break;
      case 0x05:
        cls.drawPoint(0, 0, COLOR_RED);
        cls.drawPoint(1, 0, COLOR_GREEN);
        cls.drawPoint(2, 0, COLOR_BLUE);
        break;
    }
    #endif
    step++;
    if (step > STOP) {
      step = START;
    }
    lastUpdate = millis();
  }
}

void SimpleKeypadCallback(byte id) {
  switch(id) {
    case KEYBEEPID:
      #ifdef WITHBEEP
      dp.changeValue();
      if (dp.isMinValue() || dp.isMaxValue()) {
        sm->play(jingleAlarmID);  
      } else {
        sm->play(jingleBeepID);
      }
      #endif
      break;
    case KEYBRIGHTNESSID:
      cls.changeBrightness();
      #ifdef WITHBEEP
      if (cls.isMinBrightness() || cls.isMaxBrightness()) {
        sm->play(jingleAlarmID);
      } else {
        sm->play(jingleBeepID);
      }
      #endif
      break;
  }
  observeMemory(0);
}