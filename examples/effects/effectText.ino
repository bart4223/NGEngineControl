#define DOTMATRIX //LEDSTRIP100, LEDSTRIP256, DOTMATRIX
#define SCROLLING //SINGLE, SCROLLING
#define FONTZX81 //FONTZX81

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
#define DOTMATRIXCOUNT         4
#define DOTMATRIXROWS          8
#define DOTMATRIXCOLS         32
#define DOTMATRIXBRIGHTNESS 0.05
#endif

#define DELAY   150

#ifdef LEDSTRIP256
NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS, lskUpDownAlternate);
#endif
#ifdef LEDSTRIP100
NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS);
#endif
#ifdef DOTMATRIX
NG8x8DotMatrix *cdm = new NG8x8DotMatrix(DOTMATRIXCOUNT, DOTMATRIXROWS, DOTMATRIXCOLS, dmamInverse, dmrMirroredXY);
#endif

#ifdef FONTZX81
NGZX81Font *font = new NGZX81Font();
#endif
#ifdef SINGLE
NGColorDotMatrixEffectText *effect = new NGColorDotMatrixEffectText(cdm, COLOR_RED, font);
#endif
#ifdef SCROLLING
NGColorDotMatrixEffectText *effectOne = new NGColorDotMatrixEffectText(cdm, COLOR_RED, font, setkFull);
NGColorDotMatrixEffectText *effectTwo = new NGColorDotMatrixEffectText(cdm, COLOR_RED, font, setkFull);
#endif

int posx[2] = {33, 97};

void setup() {
  observeMemory(0);
  #ifdef DOTMATRIX
  cdm->initialize(DOTMATRIXBRIGHTNESS);
  #else
  cdm->initialize(LEDSTRIPBRIGHTNESS);
  #endif
  #ifdef SINGLE
  effect->initialize();
  effect->setPosition(0, 0);
  //effect->setDelay(100);
  effect->setText("ARDCADE");
  #endif
  #ifdef SCROLLING
  effectOne->initialize();
  effectTwo->initialize();
  effectOne->setText("SBC MAN");
  effectTwo->setText("SBC MAN");
  #endif
  observeMemory(0);
}

void loop() {
  #ifdef SINGLE
  effect->processingLoop();
  #endif
  #ifdef SCROLLING
  effectOne->setPosition(posx[0], 0);
  effectTwo->setPosition(posx[1], 0);
  effectOne->processingLoop();
  effectTwo->processingLoop();
  for(int i = 0; i < 2; i++) {
    posx[i]--;
    if(posx[i] < -56) {
      switch(i) {
        case 0:
          posx[i] = posx[1] + 64;
          break;
        case 1:
          posx[i] = posx[0] + 64;
          break;
      }
    }
  }
  #endif
  delay(DELAY);
}