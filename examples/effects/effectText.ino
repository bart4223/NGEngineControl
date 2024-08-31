#define LEDSTRIP100 //LEDSTRIP100, LEDSTRIP256

#include <NGMemoryObserver.h>
#include <NGColorLEDStrip.h>
#include <NGColorDotMatrixEffectText.h>
#include <NGZX81Font.h>

#ifdef LEDSTRIP256
#define LEDSTRIPPIN           8
#define LEDSTRIPPIXELS      256
#define LEDSTRIPROWS         16
#endif
#ifdef LEDSTRIP100
#define LEDSTRIPPIN           8
#define LEDSTRIPPIXELS      100
#define LEDSTRIPROWS         10
#endif
#define LEDSTRIPBRIGHTNESS 0.05

#ifdef LEDSTRIP256
NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS, lskUpDownAlternate);
#endif
#ifdef LEDSTRIP100
NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS);
#endif

NGZX81Font *fontZX81 = new NGZX81Font();
NGColorDotMatrixEffectText *effect = new NGColorDotMatrixEffectText(cdm, COLOR_RED, fontZX81);

void setup() {
  observeMemory(0);
  cdm->initialize(LEDSTRIPBRIGHTNESS);
  effect->initialize();
  effect->setPosition(1, 1);
  //effect->setDelay(100);
  effect->setText("ARDCADE");
  observeMemory(0);
}

void loop() {
  effect->processingLoop();
}
