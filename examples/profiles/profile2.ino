#include <NGEngineControl.h>

NGEngineControl engine0 = NGEngineControl(ENGINE_0);

void setup() {
  engine0.initialize();
}

void loop() {
  engine0.setSpeed(100,2000);
  engine0.run(FORWARD);
  delay(2000);
  engine0.setSpeed(MAXSPEED,1000);
  delay(2000);
  engine0.setSpeed(150,3000);
  delay(2000);
  engine0.stop(1000);
  delay(1000);
}
