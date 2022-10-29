#define PROD false //false,true

#include <NGMemoryObserver.h>
#include <NGColorDotMatrixBinaryClock.h>

#define DELAY 500

NGColorDotMatrix cdm = NGColorDotMatrix();
NGColorDotMatrixBinaryClock cdmbc = NGColorDotMatrixBinaryClock(&cdm);

void setup() {
  //cdmbc.setColorOff(COLOR_RED);
  //cdmbc.setColorOn(COLOR_YELLOW);
  cdmbc.initialize();
}

void loop() {
  cdmbc.processingLoop();
  #if (PROD == false)
  observeMemory(DELAY);
  #endif
}
