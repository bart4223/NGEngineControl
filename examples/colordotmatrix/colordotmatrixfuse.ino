#define DOTMATRIX //OLED, DOTMATRIX

#include <NGMemoryObserver.h>
#include <NGColorDotMatrixFuse.h>
#ifdef OLED
#include <NGColorOLED.h>
#endif
#ifdef DOTMATRIX
#include <NGColorDotMatrix.h>
#endif

#define DEFPOSX 0
#define DEFPOSY 0

#define DELAY 1000

#ifdef DOTMATRIX
NGColorDotMatrix cdm = NGColorDotMatrix();
#endif
#ifdef OLED
NGColorOLED cdm = NGColorOLED();
#endif
NGColorDotMatrixFuse cdmfFuse = NGColorDotMatrixFuse(&cdm, 8, DEFPOSX, DEFPOSY);
//NGColorDotMatrixFuse cdmfFuse = NGColorDotMatrixFuse(&cdm, 8, fdRight, DEFPOSX + 7, DEFPOSY);
//NGColorDotMatrixFuse cdmfFuse = NGColorDotMatrixFuse(&cdm, 8, fdUp, DEFPOSX, DEFPOSY);
//NGColorDotMatrixFuse cdmfFuse = NGColorDotMatrixFuse(&cdm, 8, fdDown, DEFPOSX, DEFPOSY + 7);

byte valueFuse = 0x08;

void setup() {
  cdm.initialize();
  #ifdef OLED
  cdm.setScale(5);
  #endif
  cdm.clear();
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
