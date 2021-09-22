#include <NGSteeringControl.h>

NGSteeringControl sc = NGSteeringControl(ENGINE_0, ENGINE_1);

void setup() {
  sc.initialize();
  sc.stop();
}

void loop() {
  sc.run(edForward, random(200, MAXSPEED));
  delay(2000);
  sc.stop();
  delay(2000);
  sc.run(edBackward, random(200, MAXSPEED));
  delay(2000);
  sc.stop();
  delay(2000);
}
