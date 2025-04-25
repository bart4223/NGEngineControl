#define DOTMATRIX //COLORDOTMATRIX, LEDSTRIP, DOTMATRIX
#define FONTDEFAULT //FONTDEFAULT, FONTZX81, FONTC64
#define METRICS8x32 //METRICS8x8, METRICS8x32, METRICS8x40 

#include <NGCommon.h>
#include <NGZX81Font.h>
#include <NGC64Font.h>
#include <NGMemoryObserver.h>
#include <NGColorDotMatrixDecimalDigit.h>
#ifdef COLORDOTMATRIX
#include <NGColorDotMatrix.h>
#endif
#ifdef DOTMATRIX
#include <Visuals/NG8x8DotMatrix.h>
#define DOTMATRIXBRIGHTNESS 0.05
#endif
#ifdef LEDSTRIP
#include <NGColorLEDStrip.h>
#define LEDSTRIPPIN           6
#define LEDSTRIPPIXELS      100
#define LEDSTRIPROWS         10
#define LEDSTRIPBRIGHTNESS 0.05
#endif

#define DELAY 20

#ifdef COLORDOTMATRIX
NGColorDotMatrix *cdm = new NGColorDotMatrix();
#define ENDPOSX 8
#endif
#ifdef DOTMATRIX
#ifdef METRICS8x8
NG8x8DotMatrix *cdm = new NG8x8DotMatrix();
#define ENDPOSX 8
#endif
#ifdef METRICS8x32
NG8x8DotMatrix *cdm = new NG8x8DotMatrix(4, 8, 32, dmamInverse);
#define ENDPOSX 32
#endif
#ifdef METRICS8x40
NG8x8DotMatrix *cdm = new NG8x8DotMatrix(5, 8, 40, dmamInverse);
#define ENDPOSX 40
#endif
#endif
#ifdef LEDSTRIP
NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS);
#define ENDPOSX 10
#endif
NGColorDotMatrixDecimalDigit *cdmdd = new NGColorDotMatrixDecimalDigit(cdm);

#ifdef FONTZX81
NGZX81Font *fontZX81 = new NGZX81Font();
#endif

#ifdef FONTC64
NGC64Font *fontC64 = new NGC64Font();
#endif

#define START 0x09

byte counter = START;
int posx = 0;

void setup() {
  observeMemory(0);
  setGlobalRandomSeedAnalogInput(A0);
  #ifdef LEDSTRIP
  cdm->initialize(LEDSTRIPBRIGHTNESS);
  #endif
  #ifdef COLORDOTMATRIX
  cdm->initialize();
  #endif
  #ifdef DOTMATRIX
  cdm->initialize(DOTMATRIXBRIGHTNESS);
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
  //cdm->clear();
  cdm->drawLine(posx - 1, 0, posx - 1, cdm->getHeight(), cdm->getBackground());
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
    #ifdef FONTZX81
    cdmdd->setFont(fontZX81);
    #endif
    #ifdef FONTC64
    cdmdd->setFont(fontC64);
    #endif
    #ifdef FONTDEFAULT
    cdmdd->setFont(nullptr);
    #endif    
  } else {
    cdmdd->setFont(nullptr);
  }
}