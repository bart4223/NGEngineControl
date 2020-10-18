#include <NGEngineControl.h>

NGEngineControl Engine0 = NGEngineControl(ENGINE_0);

void setup() {
  Engine0.initialize();
}

void loop() {
  Engine0.setSpeed(42);
  Engine0.run(FORWARD);
}
