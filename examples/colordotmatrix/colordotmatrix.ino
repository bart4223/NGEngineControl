#include <NGMemoryObserver.h>
#include <NGColorDotMatrix.h>

#define DELAY 100

NGColorDotMatrix cdm = NGColorDotMatrix();
colorRGB c;
  
void setup() {
  cdm.initialize();
}

void loop() {
  cdm.beginUpdate();
  cdm.clear();
  c.red = random(0, 256);
  c.green = random(0, 256);
  c.blue = random(0, 256);
  cdm.drawRect(random(0, 4), random(0, 4), random(4, 8), random(4, 8), c);
  cdm.endUpdate();
  observeMemory(DELAY);
}
