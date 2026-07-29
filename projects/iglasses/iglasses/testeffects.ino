#include <NGEngineCore.h>
#include <Visuals/NGColorLEDStrip.h>
#include <Effects/NGGlassesLEDStripEffect.h>

#define LEDSTRIPPIN      8
#define LEDSTRIPPIXELS  24
#define LEDSTRIPROWS     2

#define BRIGHTNESS_DEFAULT 0.05

NGColorLEDStrip cls = NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS);
NGGlassesLEDStripEffect effect = NGGlassesLEDStripEffect(&cls);

void setup() {
  observeMemory(0);
  cls.initialize(BRIGHTNESS_DEFAULT);
  effect.initialize();
  effect.setKind(glekRotateThree);
  effect.setColor(COLOR_YELLOW);
  effect.setDelay(50);
  observeMemory(0);
}

void loop() {
  effect.processingLoop();
}