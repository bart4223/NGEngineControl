#include <NGEngineCore.h>
#include <Effects/NGSimpleCircleLEDStripEffect.h>

#define PINLEDSTRIP        8
#define LEDSTRIP_PIXELS  113
#define LEDSTRIP_RADIUS    7

#define BRIGHTNESS 0.05

#define STEPDELAY  50

NGCircleLEDStrip cls = NGCircleLEDStrip(PINLEDSTRIP, LEDSTRIP_PIXELS, LEDSTRIP_RADIUS);
//NGSimpleCircleLEDStripEffect effect = NGSimpleCircleLEDStripEffect(&cls);
NGSimpleCircleLEDStripEffect effect = NGSimpleCircleLEDStripEffect(&cls, sclsekPulse);

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
  //effect.setEffectColors(COLOR_GREEN);
  effect.setEffectColors(COLOR_BLUE, COLOR_YELLOW);
  effect.initialize();
  observeMemory(0);
}

void loop() {
  effect.processingLoop();
}