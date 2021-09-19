#include <NGSteeringControl.h>

NGSteeringControl sc = NGSteeringControl(ENGINE_0, ENGINE_1);

void setup() {
  sc.initialize();
  sc.stop();
}

void loop() {
  sc.runFullSpeedForward();
  delay(2000);
  sc.stop();
  delay(2000);
  sc.runFullSpeedBackward();
  delay(2000);
  sc.stop();
  delay(2000);
}
