#include <NGMemoryObserver.h>
#include <NGJoystickControl.h>

#define PIN 13
#define DELAY 500

#define THRESHOLDUP       100
#define THRESHOLDDOWN     923
#define THRESHOLLEFT      100
#define THRESHOLDRIGHT    923

NGJoystickControl ysc = NGJoystickControl();

void setup() {
  ysc.registerAction(PIN, jamTriggerHIGH, jaX, jtkLess, THRESHOLLEFT, DELAY);
  ysc.registerAction(PIN, jamTriggerHIGH, jaX, jtkGreater, THRESHOLDRIGHT, DELAY);
  ysc.registerAction(PIN, jamTriggerHIGH, jaY, jtkLess, THRESHOLDUP, DELAY);
  ysc.registerAction(PIN, jamTriggerHIGH, jaY, jtkGreater, THRESHOLDDOWN, DELAY);
  ysc.initialize();
}

void loop() {
  ysc.processingLoop();
}
