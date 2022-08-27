#include <NGCommon.h>
#include <NGMemoryObserver.h>
#include <NGServoControl.h>

#define PINSERVO  9
#define DELAY     300

#define MINPOS  30
#define MAXPOS  150

NGServoControl sc = NGServoControl(PINSERVO, DEFSERVOZEROPOSITION, MINPOS, MAXPOS);
int dir = 0;

void setup() {
  Serial.begin(DEFAULTSERIALRATE);
  sc.initialize();
}

void loop() {
  if (dir == 0) {
    if (!sc.isMaxPosition()) {
      sc.stepUp();
    } else {
      dir = 1;
      sc.stepDown();
    }
  } else {
    if (!sc.isMinPosition()) {
      sc.stepDown();
    } else {
      dir = 0;
      sc.stepUp();
    }
  }
  observeMemory(DELAY);
}
