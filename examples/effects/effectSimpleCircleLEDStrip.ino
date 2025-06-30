#define EFFECTTHREE //EFFECTONE, EFFECTTWO, EFFECTTHREE

#include <NGEngineCore.h>
#include <Effects/NGSimpleCircleLEDStripEffect.h>
#include <Effects/NGSymbolCircleLEDStripEffect.h>

#define PINLEDSTRIP        8
#define LEDSTRIP_PIXELS  113
#define LEDSTRIP_RADIUS    7

#define BRIGHTNESS 0.05

#ifdef EFFECTONE
#define STEPDELAY  50
#endif
#ifdef EFFECTTWO
#define STEPDELAY  50
#endif
#ifdef EFFECTTHREE
#define STEPDELAY  500
#endif

NGCircleLEDStrip cls = NGCircleLEDStrip(PINLEDSTRIP, LEDSTRIP_PIXELS, LEDSTRIP_RADIUS);
#ifdef EFFECTONE
NGSimpleCircleLEDStripEffect effect = NGSimpleCircleLEDStripEffect(&cls, sclsekPulse);
#endif
#ifdef EFFECTTWO
NGSimpleCircleLEDStripEffect effect = NGSimpleCircleLEDStripEffect(&cls, sclsekPulse);
#endif
#ifdef EFFECTTHREE
NGSymbolCircleLEDStripEffect effect = NGSymbolCircleLEDStripEffect(&cls, syclsekOnAir);
#endif

void setup() {
  observeMemory(0);
  // Circle LED Strip
  cls.setBrightness(BRIGHTNESS);
  cls.registerRadius(1, 0);  // 1 Pixel
  cls.registerRadius(2, 1);  // 8 Pixel
  cls.registerRadius(3, 9);  // 12 Pixel
  cls.registerRadius(4, 21); // 16 Pixel
  cls.registerRadius(5, 37); // 20 Pixel
  cls.registerRadius(6, 57); // 24 Pixel
  cls.registerRadius(7, 81); // 32 Pixel
  cls.setAngleOffset(180);
  // Effect
  effect.setStepDelay(STEPDELAY);
  #ifdef EFFECTONE
  effect.setEffectColors(COLOR_GREEN);
  #endif
  #ifdef EFFECTTWO
  effect.setEffectColors(COLOR_BLUE, COLOR_YELLOW);
  #endif
  #ifdef EFFECTTHREE
  effect.setSymbolColors(COLOR_PURPLE, COLOR_WHITE);
  #endif
  effect.initialize();
  observeMemory(0);
}

void loop() {
  effect.processingLoop();
}