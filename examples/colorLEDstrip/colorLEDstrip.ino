#define LEDSTRIP100 //LEDSTRIP100, LEDSTRIP256
#define TESTMODEPIXEL //TESTMODEDEFAULT, TESTMODEPIXEL

#include <NGCommon.h>
#include <NGMemoryObserver.h>
#include <NGColorLEDStrip.h>
#define PIN           8
#ifdef LEDSTRIP100
#define PIXELS      100
#define ROWS         10
#endif
#ifdef LEDSTRIP256
#define PIXELS      256
#define ROWS         16
#endif
#define BRIGHTNESS 0.05

#define DELAY        500
#ifdef TESTMODEPIXEL
#define TESTRUNS       1
#else
#define TESTRUNS       3
#endif
#define TESTDELAY    100
#define TESTMODEDELAY 20

#define START 0x00
#define STOP  0x05

#ifdef LEDSTRIP100
NGColorLEDStrip cls = NGColorLEDStrip(PIN, PIXELS, ROWS);
#endif
#ifdef LEDSTRIP256
NGColorLEDStrip cls = NGColorLEDStrip(PIN, PIXELS, ROWS, lskUpDownAlternate);
#endif

coord2D img[] = {{0, 0}, {1, 1}, {2, 2}};
colorRGB clr[] = {COLOR_RED, COLOR_GREEN, COLOR_BLUE};

byte step = START;

void setup() {
  observeMemory(0);
  initGlobalRandomSeedWithAnalogInput(A5);
  cls.setOffset(0, 0);
  //cls.setTestColor(COLOR_WHITE);
  #ifdef TESTMODEPIXEL
  cls.setTestMode(tmPixel);
  cls.setTestModeDelay(TESTMODEDELAY);
  #endif
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
