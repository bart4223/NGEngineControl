#define LEDSTRIP //OLED, DOTMATRIX, LEDSTRIP

#include <NGMemoryObserver.h>
#include <NGColorDotMatrixFuse.h>
#ifdef OLED
#include <NGColorOLED.h>
#endif
#ifdef DOTMATRIX
#include <NGColorDotMatrix.h>
#endif
#ifdef LEDSTRIP
#include <NGColorLEDStrip.h>
#define LEDSTRIPPIN           6
#define LEDSTRIPPIXELS      100
#define LEDSTRIPROWS         10
#define LEDSTRIPBRIGHTNESS 0.05
#endif

#define DEFPOSX 0
#define DEFPOSY 0

#define DELAY 1000

#ifdef DOTMATRIX
NGColorDotMatrix cdm = NGColorDotMatrix();
#define FUSEVALUE 8
#endif
#ifdef OLED
NGColorOLED cdm = NGColorOLED();
#define FUSEVALUE 8
#endif
#ifdef LEDSTRIP
NGColorLEDStrip cdm = NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS);
#define FUSEVALUE 10
#endif
NGColorDotMatrixFuse cdmfFuse = NGColorDotMatrixFuse(&cdm, FUSEVALUE, DEFPOSX, DEFPOSY);
//NGColorDotMatrixFuse cdmfFuse = NGColorDotMatrixFuse(&cdm, FUSEVALUE, fdRight, DEFPOSX + 7, DEFPOSY);
//NGColorDotMatrixFuse cdmfFuse = NGColorDotMatrixFuse(&cdm, FUSEVALUE, fdUp, DEFPOSX, DEFPOSY);
//NGColorDotMatrixFuse cdmfFuse = NGColorDotMatrixFuse(&cdm, FUSEVALUE, fdDown, DEFPOSX, DEFPOSY + 7);

byte valueFuse = FUSEVALUE;

void setup() {
  #ifdef OLED
  cdm.setScale(5);
  #endif
  #ifdef LEDSTRIP
  cdm.initialize(LEDSTRIPBRIGHTNESS);
  #else
  cdm.initialize();
  #endif
  cdm.clear();
  cdmfFuse.setColorOff(COLOR_GREEN);
  cdmfFuse.setColorOn(COLOR_RED);
  cdmfFuse.setValue(valueFuse);
}

void loop() {
  observeMemory(DELAY);
  if (valueFuse == 0) {
    valueFuse = FUSEVALUE + 1;
  }
  valueFuse--;
  cdmfFuse.setValue(valueFuse);
}
