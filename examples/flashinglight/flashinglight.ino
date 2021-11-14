#include <NGFlashingLight.h>

NGFlashingLight fl = NGFlashingLight(8, 250);

void setup() {
  fl.initialize();
  fl.setOn();
}

void loop() {
  fl.processingLoop();
}
