#define LEDSTRIP //OLED, DOTMATRIX, LEDSTRIP
#define MODE01 //MODE01, MODE02

#include <NGMemoryObserver.h>
#include <NGColorDotMatrixBinaryDigit.h>
#ifdef DOTMATRIX
#include <NGColorDotMatrix.h>
#endif
#ifdef OLED
#include <NGColorOLED.h>
#endif
#ifdef LEDSTRIP
#include <NGColorLEDStrip.h>
#define LEDSTRIPPIN           6
#define LEDSTRIPPIXELS      100
#define LEDSTRIPROWS         10
#define LEDSTRIPBRIGHTNESS 0.05
#endif

#define DEFPOSX 6
#define DEFPOSY 5

#define DELAY 1000

#ifdef DOTMATRIX
NGColorDotMatrix cdm = NGColorDotMatrix();
#endif
#ifdef OLED
NGColorOLED cdm = NGColorOLED();
#endif
#ifdef LEDSTRIP
NGColorLEDStrip cdm = NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS);
#endif
#ifdef MODE01
NGColorDotMatrixBinaryDigit cdmbdScore = NGColorDotMatrixBinaryDigit(&cdm, 5, DEFPOSX - 6, DEFPOSY);
NGColorDotMatrixBinaryDigit cdmbdLives = NGColorDotMatrixBinaryDigit(&cdm, 2, DEFPOSX - 6, DEFPOSY + 2);
#endif
#ifdef MODE02
NGColorDotMatrixBinaryDigit cdmbdSecTens = NGColorDotMatrixBinaryDigit(&cdm, 3, DEFPOSX - 1, DEFPOSY);
NGColorDotMatrixBinaryDigit cdmbdSecOne = NGColorDotMatrixBinaryDigit(&cdm, DEFPOSX, DEFPOSY);
#endif
//NGColorDotMatrixBinaryDigit cdmbdSecTens = NGColorDotMatrixBinaryDigit(&cdm, 3, bddDown, DEFPOSX - 1, DEFPOSY);
//NGColorDotMatrixBinaryDigit cdmbdSecOne = NGColorDotMatrixBinaryDigit(&cdm, 4, bddDown, DEFPOSX, DEFPOSY);
//NGColorDotMatrixBinaryDigit cdmbdSecTens = NGColorDotMatrixBinaryDigit(&cdm, 3, bddLeft, DEFPOSX, DEFPOSY - 1);
//NGColorDotMatrixBinaryDigit cdmbdSecOne = NGColorDotMatrixBinaryDigit(&cdm, 4, bddLeft, DEFPOSX, DEFPOSY);
//NGColorDotMatrixBinaryDigit cdmbdSecTens = NGColorDotMatrixBinaryDigit(&cdm, 3, bddRight, DEFPOSX, DEFPOSY - 1);
//NGColorDotMatrixBinaryDigit cdmbdSecOne = NGColorDotMatrixBinaryDigit(&cdm, 4, bddRight, DEFPOSX, DEFPOSY);

byte valueSecTens = 0x00;
byte valueSecOne = 0x00;
byte valueScore = 0x00;
byte valueLives = 0x03;

void setup() {
  #ifdef LEDSTRIP
  cdm.initialize(LEDSTRIPBRIGHTNESS);
  #else
  cdm.initialize();
  #endif
  #ifdef OLED
  cdm.setScale(8);
  #endif
  cdm.clear();
  #ifdef MODE01
  cdmbdScore.setColorOff(COLOR_BLACK);
  cdmbdScore.setColorOn(COLOR_GREEN);
  cdmbdScore.setValue(valueScore);
  cdmbdLives.setColorOff(COLOR_BLACK);
  cdmbdLives.setColorOn(COLOR_RED);
  cdmbdLives.setValue(valueLives);
  #endif
  #ifdef MODE02
  cdmbdSecTens.setColorOff(COLOR_RED);
  cdmbdSecTens.setColorOn(COLOR_YELLOW);
  cdmbdSecTens.setValue(valueSecTens);
  cdmbdSecOne.setColorOff(COLOR_RED);
  cdmbdSecOne.setColorOn(COLOR_YELLOW);
  cdmbdSecOne.setValue(valueSecOne);
  #endif
}

void loop() {
  observeMemory(DELAY);
  valueScore++;
  valueLives--;
  #ifdef MODE01
  cdmbdScore.setValue(valueScore);
  cdmbdLives.setValue(valueLives);
  #endif
  #ifdef MODE02
  valueSecOne++;
  if (valueSecOne > 0x09) {
    valueSecOne = 0x00;
  }
  valueSecTens++;
  if (valueSecTens > 0x05) {
    valueSecTens = 0x00;
  }
  cdmbdSecTens.setValue(valueSecTens);
  cdmbdSecOne.setValue(valueSecOne);
  #endif
}
