#include <NGEngineControl.h>

NGEngineControl engine = NGEngineControl(ENGINE_0);

void setup() {
  engine.initialize();
  engine.setSpeed(MAXSPEED,2000);
}

void loop() {
  engine.run(edForward);
  delay(8000);
  engine.stop();
  delay(2000);
  engine.run(edBackward);
  delay(8000);
  engine.stop();
  delay(2000);
}
