#include <NGMemoryObserver.h>
#include <NGHallSensor.h>

#define DELAY 1000

NGHallSensor hs = NGHallSensor();

void setup() {
  observeMemory(0);
  hs.initialize();
  observeMemory(0);
}

void loop() {
  if (hs.isMagneticFieldDetected()) {
    Serial.println("Door is closed");
  } else {
    Serial.println("Door is opened");
  }
  observeMemory(DELAY);
}