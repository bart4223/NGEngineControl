#define LEDSTRIP //DOTMATRIX, LEDSTRIP
#define C64 // DEFAULT, ZX81, C64

#include <NGCommon.h>
#ifdef ZX81
#include <NGZX81Font.h>
#endif
#ifdef C64
#include <NGC64Font.h>
#endif
#include <NGMemoryObserver.h>
#include <NGColorDotMatrixCharDigit.h>
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
NGColorDotMatrixCharDigit *cdmcd = new NGColorDotMatrixCharDigit(cdm);

#ifdef DEFAULT
#define MAXLETTER 3
#endif
#ifdef ZX81
#define MAXLETTER 3
NGZX81Font *fontZX81 = new NGZX81Font();
#endif
#ifdef C64
#define MAXLETTER 2
NGC64Font *fontC64 = new NGC64Font();
#endif

int posx = 0;
int letter = -1;

void setup() {
  observeMemory(0);
  #ifdef LEDSTRIP
  cdm->initialize(LEDSTRIPBRIGHTNESS);
  cdm->setOffset(1, 1);
  #else
  cdm->initialize();
  #endif
  //cdmcd->setRandomColorBackground(true);
  //cdmcd->setColorBackground(COLOR_RED);
  //cdmcd->setRandomColor(true);
  #ifdef ZX81
  cdmcd->setFont(fontZX81);
  #endif
  #ifdef C64
  cdmcd->setFont(fontC64);
  #endif
  cdmcd->setColor(COLOR_GREEN);
  cdmcd->setPosX(posx);
  initLetter();
  observeMemory(0);
}

void loop() {
  delay(DELAY);
  posx++;
  cdm->beginUpdate();
  cdm->clear();
  cdmcd->setPosX(posx);
  if (posx == ENDPOSX) {
    posx = -1;
    initLetter();
  }
  cdm->endUpdate();
}

void initLetter() {
  letter++;
  if (letter > MAXLETTER) {
    letter = 0;
  }
  switch(letter) {
    case 0:
      #ifdef ZX81
      cdmcd->setChar('Z');
      #endif
      #ifdef C64
      cdmcd->setChar('C');
      #endif
      break;
    case 1:
      #ifdef ZX81
      cdmcd->setChar('X');
      #endif
      #ifdef C64
      cdmcd->setChar('6');
      #endif
      break;
    case 2:
      #ifdef ZX81
      cdmcd->setChar('8');
      #endif
      #ifdef C64
      cdmcd->setChar('4');
      #endif
      break;
    case 3:
      #ifdef ZX81
      cdmcd->setChar('1');
      #endif
      break;
  }
}
