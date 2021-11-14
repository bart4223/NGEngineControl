#include <NGLightSensor.h>

NGLightSensor ls = NGLightSensor();

void setup() {
  ls.registerThreshold(650, tlUnder, 4, tvHigh, 100);
  ls.initialize();
}

void loop() {
  ls.determine();
}
