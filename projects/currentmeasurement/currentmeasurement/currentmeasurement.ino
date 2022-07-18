#include <NGMemoryObserver.h>
#include <NGCurrentSensor.h>

NGCurrentSensor cs = NGCurrentSensor(cst20Ampere);

void setup() {
  Serial.begin(9600);
  cs.initialize();
}

void loop() {
  char log[100];
  sprintf(log, "%d mA", cs.getCurrentAbs());
  Serial.println(log);
  observeMemory(1000);
}
