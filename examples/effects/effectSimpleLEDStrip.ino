#include <NGMemoryObserver.h>
#include <NGColorLEDStrip.h>
#include <Effects/NGSimpleColorLEDStripEffect.h>

#define PINLEDSTRIP         8
#define LEDSTRIP8_PIXELS    8
#define LEDSTRIP8_ROWS      1

#define BRIGHTNESS 0.05

#define STEPDELAY   250

NGColorLEDStrip cls = NGColorLEDStrip(PINLEDSTRIP, LEDSTRIP8_PIXELS, LEDSTRIP8_ROWS);
NGSimpleColorLEDStripEffect effect = NGSimpleColorLEDStripEffect(&cls, slsekAlternate);

void setup() {
  observeMemory(0);
  // LED Strip
  cls.setBrightness(BRIGHTNESS);
  // Effect
  effect.setStepDelay(STEPDELAY);
  effect.setEffectColors(COLOR_RED);
  effect.initialize();
  observeMemory(0);
}

void loop() {
  effect.processingLoop();
}