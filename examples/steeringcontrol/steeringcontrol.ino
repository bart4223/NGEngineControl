#include <NGSteeringControl.h>

#define MXLOOPS 2

NGSteeringControl sc = NGSteeringControl();
int index = 0;

void setup() {
  sc.initialize();
}

void loop() {
  if (index < MXLOOPS) {
    sc.run(edForward, 50);
    delay(1000);
    sc.run(edBackward, 50);
    delay(1000);
    sc.stop();
    index++;
  }
}
