#include <NGCommon.h>
#include <NGMemoryObserver.h>
#include <NGServoControl.h>

#define PINSERVO  9
#define DELAY     20

#define MINPOS  65
#define MAXPOS  125
#define ZEROPOS 95
#define STEP    1

NGServoControl sc = NGServoControl(PINSERVO, ZEROPOS, MINPOS, MAXPOS, STEP);
bool play = true; //false
bool logging = false; //false
int dir = 0;

void setup() {
  Serial.begin(DEFAULTSERIALRATE);
  sc.initialize();
  sc.setLogging(logging);
}

void loop() {
  if (play) {
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
