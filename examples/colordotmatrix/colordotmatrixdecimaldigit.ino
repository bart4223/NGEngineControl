#define LEDSTRIP //DOTMATRIX, LEDSTRIP

#include <NGCommon.h>
#include <NGZX81Font.h>
#include <NGMemoryObserver.h>
#include <NGColorDotMatrixDecimalDigit.h>
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

#define DELAY 100

#ifdef DOTMATRIX
NGColorDotMatrix *cdm = new NGColorDotMatrix();
#define ENDPOSX 7
#endif
#ifdef LEDSTRIP
NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS);
#define ENDPOSX 9
#endif
NGColorDotMatrixDecimalDigit *cdmdd = new NGColorDotMatrixDecimalDigit(cdm);

NGZX81Font *fontZX81 = new NGZX81Font();

#define START 0x09

byte counter = START;
int posx = 0;

void setup() {
  observeMemory(0);
  #ifdef LEDSTRIP
  cdm->initialize(LEDSTRIPBRIGHTNESS);
  #else
  cdm->initialize();
  #endif
  //cdmdd->setRandomColorBackground(true);
  //cdmdd->setColorBackground(COLOR_RED);
  //cdmdd->setRandomColor(true);
  cdmdd->setColor(COLOR_GREEN);
  cdmdd->setPosX(posx);
  cdmdd->setValue(counter);
  observeMemory(0);
}

void loop() {
  delay(DELAY);
  posx++;
  cdm->beginUpdate();
  cdm->clear();
  cdmdd->setPosX(posx);
  if (posx == ENDPOSX) {
    posx = -1;
    if (counter == 0) {
      counter = START;
    } else {
      counter--;
    }
    randomFont();
    cdmdd->setValue(counter);
  }
  cdm->endUpdate();
}

void randomFont() {
  if (getYesOrNo()) {
    cdmdd->setFont(fontZX81);
  } else {
    cdmdd->setFont(nullptr);
  }
}
