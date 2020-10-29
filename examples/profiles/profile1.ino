#include <NGEngineControl.h>

NGEngineControl engine0 = NGEngineControl(ENGINE_0);

void setup() {
  engine0.initialize();
}

void loop() {
  engine0.setSpeed(200,2000);
  engine0.run(FORWARD);
  delay(1000);
  engine0.stop();
  delay(2000);
}
