#include <NGMemoryObserver.h>
#include <NGLightSensor.h>

#define DELAY 500

NGLightSensor ls = NGLightSensor();

void setup() {
  observeMemory(0);
  //ls.setLogging(true);
  ls.registerThreshold(650, tlUnder, 4, tvHigh, 100);
  ls.initialize();
  observeMemory(0);
}

void loop() {
  ls.processingLoop();
  //observeMemory(DELAY);
}
