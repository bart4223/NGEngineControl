#include <NGMemoryObserver.h>
#include <Sensors/NGSimpleDigitalSensor.h>

#define PINSENSOR 5

#define DELAY 500

NGSimpleDigitalSensor sds = NGSimpleDigitalSensor(PINSENSOR);

void setup() {
  observeMemory(0);
  sds.initialize();
  observeMemory(0);
}

void loop() {
  if (sds.isOn()) {
    Serial.println("Is on");
  }
  observeMemory(DELAY);
}