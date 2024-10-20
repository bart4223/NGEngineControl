#define LEDSTRIPAUTO //LEDSTRIP100, LEDSTRIP256, LEDSTRIPAUTO
#define TESTMODEDEFAULT //TESTMODEDEFAULT, TESTMODEPIXEL

#include <NGCommon.h>
#include <NGMemoryObserver.h>
#include <NGColorLEDStrip.h>

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

coord2D img[] = {{0, 0}, {1, 1}, {2, 2}};
colorRGB clr[] = {COLOR_RED, COLOR_GREEN, COLOR_BLUE};

byte step = START;

void setup() {
  observeMemory(0);
  initGlobalRandomSeedWithAnalogInput(A5);
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
  observeMemory(0);
}

void loop() {
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
  delay(DELAY);
}
