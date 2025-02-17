#define PROD true //false, true

#include <NGMemoryObserver.h>
#include <NGHallSensor.h>
#include <NGSimpleLED.h>
#include <Effects/NGSimpleLEDEffect.h>

#define PINLED1 6
#define PINLED2 7

#define DELAY     1000
#define STEPDELAY  150

NGHallSensor hs = NGHallSensor();
NGSimpleLED led1 = NGSimpleLED(PINLED1);
NGSimpleLED led2 = NGSimpleLED(PINLED2);
NGSimpleLEDEffect se = NGSimpleLEDEffect();

void setup() {
  observeMemory(0);
  hs.initialize();
  se.setStepDelay(STEPDELAY);
  se.registerLED(&led1);
  se.registerLED(&led2);
  se.initialize();
  observeMemory(0);
}

void loop() {
  if (hs.isMagneticFieldDetected()) {
    se.effectOff();
  } else {
    se.effectOn();
  }
  se.processingLoop();
  #if (PROD == false)
  observeMemory(DELAY);
  #endif
}