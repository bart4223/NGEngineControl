#include <NGEngineControl.h>

NGEngineControl engine = NGEngineControl(ENGINE_0);

void setup() {
  engine.initialize();
}

void loop() {
  engine.setSpeed(100,2000);
  engine.run(edForward);
  delay(2000);
  engine.setSpeed(MAXSPEED,1000);
  delay(2000);
  engine.setSpeed(150,3000);
  delay(2000);
  engine.stop(1000);
  delay(1000);
}
