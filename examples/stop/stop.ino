#include <NGEngineControl.h>

NGEngineControl engine0 = NGEngineControl(ENGINE_0);
NGEngineControl engine1 = NGEngineControl(ENGINE_1);
NGEngineControl engine2 = NGEngineControl(ENGINE_2);
NGEngineControl engine3 = NGEngineControl(ENGINE_3);

void setup() {
  engine0.initialize();
  engine0.stop();
  engine1.initialize();
  engine1.stop();
  engine2.initialize();
  engine2.stop();
  engine3.initialize();
  engine3.stop();
}

void loop() {
}
