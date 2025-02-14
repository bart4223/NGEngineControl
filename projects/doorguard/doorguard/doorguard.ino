#define PROD true //false, true

#include <NGMemoryObserver.h>
#include <NGHallSensor.h>
#include <NGSimpleLED.h>

#define DELAY 1000

NGHallSensor hs = NGHallSensor();
NGSimpleLED led = NGSimpleLED();

void setup() {
  observeMemory(0);
  hs.initialize();
  led.initialize();
  observeMemory(0);
}

void loop() {
  if (hs.isMagneticFieldDetected()) {
    led.off();
  } else {
    led.on();
  }
  #if (PROD == false)
  observeMemory(DELAY);
  #endif
}