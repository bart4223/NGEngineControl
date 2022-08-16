#include <NGMemoryObserver.h>
#include <NGJoystickControl.h>

#define PIN     3
#define DELAY 500

#define THRESHOLDUP       100
#define THRESHOLDDOWN     923
#define THRESHOLLEFT      100
#define THRESHOLDRIGHT    923

NGJoystickControl ysc = NGJoystickControl();

void setup() {
  /*
  ysc.registerAction(PIN, jamTriggerHIGH, jaX, jtkLess, THRESHOLLEFT, DELAY);
  ysc.registerAction(PIN, jamTriggerHIGH, jaX, jtkGreater, THRESHOLDRIGHT, DELAY);
  ysc.registerAction(PIN, jamTriggerHIGH, jaY, jtkLess, THRESHOLDUP, DELAY);
  ysc.registerAction(PIN, jamTriggerHIGH, jaY, jtkGreater, THRESHOLDDOWN, DELAY);
  ysc.registerAction(PIN, jamTriggerHIGH, DELAY);
  */
  ysc.registerAction(PIN, jamTriggerLOW, jaX, jtkLess, THRESHOLLEFT, DELAY);
  ysc.registerAction(PIN, jamTriggerLOW, jaX, jtkGreater, THRESHOLDRIGHT, DELAY);
  ysc.registerAction(PIN, jamTriggerLOW, jaY, jtkLess, THRESHOLDUP, DELAY);
  ysc.registerAction(PIN, jamTriggerLOW, jaY, jtkGreater, THRESHOLDDOWN, DELAY);
  ysc.registerAction(PIN, jamTriggerLOW, DELAY);
  ysc.initialize();
}

void loop() {
  ysc.processingLoop();
  //observeMemory(1000);
}
