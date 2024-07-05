#include <NGCommon.h>
#include <NGMemoryObserver.h>
#include <NGColorLED.h>

#define PINRED   2
#define PINGREEN 3
#define PINBLUE  4

#define DELAY 500
#define START 0x00
#define STOP  0x04

NGColorLED colorLED = NGColorLED(PINRED, PINGREEN, PINBLUE);
byte step = START;

void setup() {
  observeMemory(0);
  initGlobalRandomSeedWithAnalogInput(A0);
  colorLED.initialize();
  observeMemory(0);
}

void loop() {
  observeMemory(DELAY);
  switch(step) {
    case 0x00:
      colorLED.setColor(COLOR_RED);
      break;
    case 0x01:
      colorLED.setColor(COLOR_GREEN);
      break;
    case 0x02:
      colorLED.setColor(COLOR_BLUE);
      break;
    case 0x03:
      colorLED.setColor(COLOR_YELLOW);
      break;
    case 0x04:
      colorLED.setColor(getRandomColor());
      break;
  }
  step++;
  if (step > STOP) {
    step = START;
  }
}
