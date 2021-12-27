#include <NGMemoryObserver.h>
#include <NGTemperatureSensor.h>

#define PINSENSOR 2
#define DELAY 5000

NGTemperatureSensor ts = NGTemperatureSensor(PINSENSOR);

void setup() {
  ts.initialize();
}

void loop() {
  char log[100];
  sprintf(log, "%s °C", ts.getTemperatureAsChar());
  Serial.println(log);
  Serial.print(ts.getHumidityAsChar());
  Serial.println(" %");
  observeMemory(DELAY);
}
