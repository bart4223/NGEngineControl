#include <NGMemoryObserver.h>
#include <NGColorDotMatrixFuse.h>

#define DEFPOSX 0
#define DEFPOSY 0

#define DELAY 1000

NGColorDotMatrix cdm = NGColorDotMatrix();
NGColorDotMatrixFuse cdmfFuse = NGColorDotMatrixFuse(&cdm, 8, DEFPOSX, DEFPOSY);
//NGColorDotMatrixFuse cdmfFuse = NGColorDotMatrixFuse(&cdm, 8, fdRight, DEFPOSX + 7, DEFPOSY);
//NGColorDotMatrixFuse cdmfFuse = NGColorDotMatrixFuse(&cdm, 8, fdUp, DEFPOSX, DEFPOSY);
//NGColorDotMatrixFuse cdmfFuse = NGColorDotMatrixFuse(&cdm, 8, fdDown, DEFPOSX, DEFPOSY + 7);

byte valueFuse = 0x08;

void setup() {
  cdm.initialize();
  cdmfFuse.setColorOff(COLOR_GREEN);
  cdmfFuse.setColorOn(COLOR_RED);
  cdmfFuse.setValue(valueFuse);
}

void loop() {
  observeMemory(DELAY);
  if (valueFuse == 0) {
    valueFuse = 0x09;
  }
  valueFuse--;
  cdmfFuse.setValue(valueFuse);
}
