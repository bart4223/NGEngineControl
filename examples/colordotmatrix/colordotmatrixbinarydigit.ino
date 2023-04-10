#define DOTMATRIX //OLED, DOTMATRIX

#include <NGMemoryObserver.h>
#include <NGColorDotMatrixBinaryDigit.h>
#ifdef DOTMATRIX
#include <NGColorDotMatrix.h>
#endif
#ifdef OLED
#include <NGColorOLED.h>
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
NGColorDotMatrixBinaryDigit cdmbdScore = NGColorDotMatrixBinaryDigit(&cdm, 5, DEFPOSX - 6, DEFPOSY);
NGColorDotMatrixBinaryDigit cdmbdLives = NGColorDotMatrixBinaryDigit(&cdm, 2, DEFPOSX - 6, DEFPOSY + 2);
//NGColorDotMatrixBinaryDigit cdmbdSecTens = NGColorDotMatrixBinaryDigit(&cdm, 3, DEFPOSX - 1, DEFPOSY);
//NGColorDotMatrixBinaryDigit cdmbdSecOne = NGColorDotMatrixBinaryDigit(&cdm, DEFPOSX, DEFPOSY);
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
  cdm.initialize();
  #ifdef OLED
  cdm.setScale(8);
  #endif
  cdm.clear();
  cdmbdScore.setColorOff(COLOR_BLACK);
  cdmbdScore.setColorOn(COLOR_GREEN);
  cdmbdScore.setValue(valueScore);
  cdmbdLives.setColorOff(COLOR_BLACK);
  cdmbdLives.setColorOn(COLOR_RED);
  cdmbdLives.setValue(valueLives);
  //cdmbdSecTens.setColorOff(COLOR_RED);
  //cdmbdSecTens.setColorOn(COLOR_YELLOW);
  //cdmbdSecTens.setValue(valueSecTens);
  //cdmbdSecOne.setColorOff(COLOR_RED);
  //cdmbdSecOne.setColorOn(COLOR_YELLOW);
  //cdmbdSecOne.setValue(valueSecOne);
}

void loop() {
  observeMemory(DELAY);
  valueScore++;
  valueLives--;
  cdmbdScore.setValue(valueScore);
  cdmbdLives.setValue(valueLives);
  /*
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
  */
}
