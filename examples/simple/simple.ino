#include <NGEngineControl.h>

NGEngineControl Engine01 = NGEngineControl(5, 6);

void setup() {
  Engine01.initialize();
}

void loop() {
  Engine01.setSpeed(42);
  Engine01.run(FORWARD);
}
