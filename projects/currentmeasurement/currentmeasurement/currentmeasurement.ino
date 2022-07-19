#include <NGMemoryObserver.h>
#include <NGCurrentSensor.h>

NGCurrentSensor cs = NGCurrentSensor(cst20Ampere);

void setup() {
  Serial.begin(9600);
  cs.initialize();
  Serial.println("INIT");
}

void loop() {
  char log[100];
  sprintf(log, "%dmA", cs.getCurrent());
  Serial.println(log);
  sprintf(log, "min %dmA, max %dmA", cs.getMin(), cs.getMax());
  Serial.println(log);
  observeMemory(3000);
}
