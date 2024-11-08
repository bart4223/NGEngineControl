#define LEDSTRIPAUTO //LEDSTRIP100, LEDSTRIP256, LEDSTRIPAUTO
#define TESTMODEDEFAULT //TESTMODEDEFAULT, TESTMODEPIXEL
#define WITHOUTBEEP //WITHOUTBEEP, WITHBEEP

#include <NGCommon.h>
#include <NGMemoryObserver.h>
#include <NGColorLEDStrip.h>
#include <NGSimpleKeypad.h>
#ifdef WITHBEEP
#include <NGSoundMachine.h>
#include <NGJingleBeep.h>
#include <NGDigitalPotentiometer.h>
#endif

#define PIN                   8
#define PINAUTODETECTION     A0

#define LEDSTRIP100_INDICATOR 900
#define LEDSTRIP100_PIXELS    100
#define LEDSTRIP100_ROWS       10
#define LEDSTRIP256_INDICATOR 800
#define LEDSTRIP256_PIXELS    256
#define LEDSTRIP256_ROWS       16

#define BRIGHTNESS 0.05

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

#ifdef LEDSTRIPAUTO
// 1K = 100 Pixel
// 2K = 256 Pixel
NGColorLEDStrip cls = NGColorLEDStrip(PIN, PINAUTODETECTION);
#endif
#ifdef LEDSTRIP100
NGColorLEDStrip cls = NGColorLEDStrip(PIN, LEDSTRIP100_PIXELS, LEDSTRIP100_ROWS);
#endif
#ifdef LEDSTRIP256
NGColorLEDStrip cls = NGColorLEDStrip(PIN, LEDSTRIP256_PIXELS, LEDSTRIP256_ROWS, lskUpDownAlternate);
#endif

#define KEY1PIN           27
#define KEY1ID            42

#define KEYDELAY 250

NGSimpleKeypad skp = NGSimpleKeypad();

coord2D img[] = {{0, 0}, {1, 1}, {2, 2}};
colorRGB clr[] = {COLOR_RED, COLOR_GREEN, COLOR_BLUE};

byte step = START;
long lastUpdate = 0;

void setup() {
  observeMemory(0);
  initGlobalRandomSeedWithAnalogInput(A5);
  skp.registerCallback(&SimpleKeypadCallback);
  skp.registerKey(KEY1PIN, KEY1ID, KEYDELAY);
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
  dp.initialize(POTI_MAX);
  sm->setConcurrently(true);
  sm->registerJingle(new NGJingleBeep);
  sm->initialize();
  sm->activate();
  sm->playRandom();
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
    step++;
    if (step > STOP) {
      step = START;
    }
    lastUpdate = millis();
  }
}

void SimpleKeypadCallback(byte id) {
  switch(id) {
    case KEY1ID:
      cls.changeBrightness();
      #ifdef WITHBEEP
      if (cls.isMinBrightness() || cls.isMaxBrightness()) {
        sm->playRandom();
      }
      #endif
      break;
  }
  observeMemory(0);
}
