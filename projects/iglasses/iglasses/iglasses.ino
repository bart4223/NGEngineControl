#define PROD false //false, true

#include <NGEngineCore.h>
#include <NGSerialNotification.h>
#include <Visuals/NGColorLEDStrip.h>

#define LEDSTRIPPIN      8
#define LEDSTRIPPIXELS  24
#define LEDSTRIPROWS     2

#define KEYSTARTPIN      7
#define KEYSTARTID      45
#define KEYHOTPIN        6
#define KEYHOTID        44
#define KEYEFFECTPIN     5
#define KEYEFFECTID     43
#define KEYCOLORPIN      4
#define KEYCOLORID      42

#define KEYDELAY       500

#define BRIGHTNESS_LOW_PIN      9
#define BRIGHTNESS_MEDIUM_PIN  10
#define BRIGHTNESS_HIGH_PIN    11
#define BRIGHTNESS_ULTRA_PIN   12

#define BRIGHTNESS_DEFAULT 0.05
#define BRIGHTNESS_LOW     0.25
#define BRIGHTNESS_MEDIUM  0.5
#define BRIGHTNESS_HIGH    0.75
#define BRIGHTNESS_ULTRA   1.00

#define TESTMODEDELAY     40
#define TESTDELAY       2000
#define TESTRUNS           2

#if (PROD == false)
NGSerialNotification serialNotification = NGSerialNotification();
#endif
NGSimpleKeypad skp = NGSimpleKeypad();
NGColorLEDStrip cls = NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS);

void setup() {
  #if (PROD == false)
  observeMemory(0);
  #endif
  // Keypad
  skp.registerCallback(&keypadCallback);
  skp.registerKey(KEYSTARTPIN, KEYSTARTID, KEYDELAY);
  skp.registerKey(KEYHOTPIN, KEYHOTID, KEYDELAY);
  skp.registerKey(KEYEFFECTPIN, KEYEFFECTID, KEYDELAY);
  skp.registerKey(KEYCOLORPIN, KEYCOLORID, KEYDELAY);
  // Color LED Strip
  #if (PROD == false)
  initGlobalRandomSeedWithAnalogInput(A0);
  cls.setTestModeDelay(TESTMODEDELAY);
  cls.initialize(BRIGHTNESS_DEFAULT);
  for (int i = 0; i < TESTRUNS; i++) {
    cls.testSequenceStart();
    delay(TESTDELAY);
  }
  cls.testSequenceStop();
  #else
  if (IsSwitchOn(BRIGHTNESS_ULTRA_PIN)) {
    cls.initialize(BRIGHTNESS_ULTRA);
  } else if (BRIGHTNESS_HIGH_PIN) {
    cls.initialize(BRIGHTNESS_HIGH);
  } else if (BRIGHTNESS_MEDIUM_PIN) {
    cls.initialize(BRIGHTNESS_MEDIUM);
  } else if (BRIGHTNESS_LOW_PIN) {
    cls.initialize(BRIGHTNESS_LOW);
  } else {
    cls.initialize(BRIGHTNESS_DEFAULT);
  }
  #endif
  #if (PROD == false)
  observeMemory(0);
  #endif
}

void loop() {

}

void keypadCallback(byte id) {
  switch (id) {
    case KEYSTARTID:
      break;
    case KEYHOTID:
      break;
    case KEYEFFECTID:
      break;
    case KEYCOLORID:
      break;
  }
}