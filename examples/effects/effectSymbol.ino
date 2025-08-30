#define DOTMATRIX //LEDSTRIP100, LEDSTRIP256, DOTMATRIX
#define FONTWINGDINGS //FONTZX81, FONTWINGDINGS
 
#include <NGMemoryObserver.h>
#include <Visuals/NGColorLEDStrip.h>
#include <Visuals/NG8x8DotMatrix.h>
#include <Effects/NGColorDotMatrixEffectText.h>
#include <Fonts/NGWingDingsFont.h>
#include <Fonts/NGZX81Font.h>

#ifdef LEDSTRIP256
#define LEDSTRIPPIN           8
#define LEDSTRIPPIXELS      256
#define LEDSTRIPROWS         16
#define LEDSTRIPBRIGHTNESS 0.05
#endif
#ifdef LEDSTRIP100
#define LEDSTRIPPIN           8
#define LEDSTRIPPIXELS      100
#define LEDSTRIPROWS         10
#define LEDSTRIPBRIGHTNESS 0.05
#endif
#ifdef DOTMATRIX
#define DOTMATRIXBRIGHTNESS 0.05
#define DOTMATRIXCOUNT  4
#define DOTMATRIXROWS   8
#define DOTMATRIXCOLS  32
#endif

#define DELAY      150
#define DELAYTEXT 1000

#ifdef LEDSTRIP256
NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS, lskUpDownAlternate);
#endif
#ifdef LEDSTRIP100
NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS);
#endif
#ifdef DOTMATRIX
NG8x8DotMatrix *cdm = new NG8x8DotMatrix(DOTMATRIXCOUNT, DOTMATRIXROWS, DOTMATRIXCOLS, dmamInverse);
#endif

#ifdef FONTWINGDINGS
NGWingDingsFont *font = new NGWingDingsFont();
#endif
#ifdef FONTZX81
NGZX81Font *font = new NGZX81Font();
#endif
NGColorDotMatrixEffectText *effect = new NGColorDotMatrixEffectText(cdm, COLOR_RED, font);

int posx = -8;

void setup() {
  observeMemory(0);
  #ifdef DOTMATRIX
  cdm->initialize(DOTMATRIXBRIGHTNESS);
  #else
  cdm->initialize(LEDSTRIPBRIGHTNESS);
  #endif
  effect->initialize();
  effect->setDelay(DELAYTEXT);
  effect->setText("SsCB");
  observeMemory(0);
}

void loop() {
  effect->setPosition(posx, 0);
  effect->processingLoop();
  cdm->drawLine(posx - 1, 0, posx - 1, 7, COLOR_BLACK);
  posx++;
  if (posx > 32) {
    posx = -8;
  }
  delay(DELAY);
}