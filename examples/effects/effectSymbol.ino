#define DOTMATRIX //LEDSTRIP100, LEDSTRIP256, DOTMATRIX
#define FONTWINGDINGS //FONTZX81, FONTWINGDINGS
 
#include <NGMemoryObserver.h>
#include <Visuals/NGColorLEDStrip.h>
#include <Visuals/NG8x8DotMatrix.h>
#include <NGColorDotMatrixEffectText.h>
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

void setup() {
  observeMemory(0);
  #ifdef DOTMATRIX
  cdm->initialize(DOTMATRIXBRIGHTNESS);
  #else
  cdm->initialize(LEDSTRIPBRIGHTNESS);
  #endif
  effect->initialize();
  effect->setPosition(8, 0);
  effect->setDelay(100);
  effect->setText("S");
  observeMemory(0);
}

void loop() {
  effect->processingLoop();
}