#include <NGSteeringControl.h>

#define START A1

NGSteeringControl sc = NGSteeringControl(ENGINE_0, ENGINE_1);

void setup() {
  pinMode(START, INPUT_PULLUP);
  sc.initialize();
  sc.stop();
  Serial.println("wait for start...");
  while(digitalRead(START));
  Serial.println("...started");
}

void loop() {
  sc.run(edForward, random(100, MAXSPEED));
  delay(2000);
  sc.stop();
  delay(2000);
  sc.run(edBackward, random(100, MAXSPEED));
  delay(2000);
  sc.stop();
  delay(2000);
}
