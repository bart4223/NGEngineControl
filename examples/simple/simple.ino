#include <NGEngineControl.h>

NGEngineControl engine0 = NGEngineControl(ENGINE_0);

void setup() {
  engine0.initialize();
  engine0.setSpeed(255,2000);
}

void loop() {
  engine0.run(FORWARD);
  delay(8000);
  engine0.stop();
  delay(2000);
  engine0.run(BACKWARD);
  delay(8000);
  engine0.stop();
  delay(2000);
}
