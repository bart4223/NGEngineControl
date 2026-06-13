#define PROD false //false, true

#include <NGEngineCore.h>
#include <NGSerialNotification.h>
#include <Visuals/NGColorLEDStrip.h>

#define LEDSTRIPPIN      8
#define LEDSTRIPPIXELS  24
#define LEDSTRIPROWS     2

#define BRIGHTNESS     0.5

#define TESTBRIGHTNESS  0.05
#define TESTMODEDELAY     20
#define TESTDELAY        100
#define TESTRUNS           1

#if (PROD == false)
NGSerialNotification serialNotification = NGSerialNotification();
#endif
NGColorLEDStrip cls = NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS);

void setup() {
  observeMemory(0);
  #if (PROD == false)
  cls.setTestModeDelay(TESTMODEDELAY);
  cls.initialize(TESTBRIGHTNESS);
  for (int i = 0; i < TESTRUNS; i++) {
    cls.testSequenceStart();
    delay(TESTDELAY);
  }
  cls.testSequenceStop();
  #else
  cls.initialize(BRIGHTNESS);
  #endif
  observeMemory(0);
}

void loop() {

}