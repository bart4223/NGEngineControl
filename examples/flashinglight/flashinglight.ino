#include <NGFlashingLight.h>

#define DELAY 2000

NGFlashingLight fl = NGFlashingLight(8, 250);

void setup() {
  fl.initialize();
  fl.testSequenceStart();
  delay(DELAY);
  fl.testSequenceStop();
  fl.setOn(true);
}

void loop() {
  fl.processingLoop();
}
