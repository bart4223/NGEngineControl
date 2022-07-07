#include <NGEngineControl.h>

NGEngineControl engine = NGEngineControl(ENGINE_0);

void setup() {
  engine.initialize();
}

void loop() {
  engine.setSpeed(200,2000);
  engine.run(edForward);
  delay(1000);
  engine.stop();
  delay(2000);
}
