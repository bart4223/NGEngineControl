#include <NGMemoryObserver.h>
#include <NGColorLEDStrip.h>

#define PIN      6
#define PIXELS 100
#define ROWS    10

#define DELAY       500
#define TESTRUNS      5
#define TESTDELAY   100
#define BRIGHTNESS 0.05

#define START 0x00
#define STOP  0x04

NGColorLEDStrip cls = NGColorLEDStrip(PIN, PIXELS, ROWS);

coord2D img[] = {{0, 0}, {1, 1}, {2, 2}};
colorRGB clr[] = {COLOR_RED, COLOR_GREEN, COLOR_BLUE};

byte step = START;

void setup() {
  observeMemory(0);
  cls.setOffset(0, 0);
  //cls.setTestColor(COLOR_WHITE);
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
  }
  step++;
  if (step > STOP) {
    step = START;
  }
  delay(DELAY);
}
