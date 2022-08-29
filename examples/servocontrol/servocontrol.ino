#include <NGCommon.h>
#include <NGMemoryObserver.h>
#include <NGServoControl.h>

#define PINSERVO  9
#define DELAY     20

#define ZEROPOS 100
#define RANGE   30
#define MINPOS  ZEROPOS - RANGE
#define MAXPOS  ZEROPOS + RANGE
#define STEP    1

NGServoControl sc = NGServoControl(PINSERVO, ZEROPOS, MINPOS, MAXPOS, STEP);
int loops = 2; // 0
bool logging = false; //false
int dir = 0;

void setup() {
  Serial.begin(DEFAULTSERIALRATE);
  sc.initialize();
  sc.setLogging(logging);
}

void loop() {
  if (loops > 0) {
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
        loops--;
        if (loops == 0) {
          sc.reset();
        }
      }
    }
    if (logging) {
      observeMemory(DELAY);
    } else {
      delay(DELAY);
    }
  } else if (logging) {
      observeMemory(10 * DELAY);
  } else {
    delay(DELAY);
  }
}
