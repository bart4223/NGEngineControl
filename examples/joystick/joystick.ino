#include <NGMemoryObserver.h>
#include <NGJoystickControl.h>

#define LOGGING false // false

#define JOYSTICKID       0
#define JOYSTICKPINX    A0
#define JOYSTICKPINY    A1
#define JOYSTICKPINFIRE  8

#define PINUP     3
#define PINDOWN   4
#define PINLEFT   5
#define PINRIGHT  6
#define PINFIRE   7

#define DELAY 100

#define THRESHOLDUP       512 // 100
#define THRESHOLDDOWN     511 // 923
#define THRESHOLDLEFT     516 // 100
#define THRESHOLDRIGHT    515 // 923

NGJoystickControl jsc = NGJoystickControl(JOYSTICKID, JOYSTICKPINX, JOYSTICKPINY, JOYSTICKPINFIRE);

void setup() {
  observeMemory(0);
  jsc.setLogging(LOGGING);
  jsc.registerActionCallback(&joystickActionCallback);
  jsc.registerActionValueCallback(&joystickActionValueCallback);
  /*
  jsc.registerAction(PIN, jamTriggerHIGH, jaX, jtkLess, THRESHOLLEFT, DELAY);
  jsc.registerAction(PIN, jamTriggerHIGH, jaX, jtkGreater, THRESHOLDRIGHT, DELAY);
  jsc.registerAction(PIN, jamTriggerHIGH, jaY, jtkLess, THRESHOLDUP, DELAY);
  jsc.registerAction(PIN, jamTriggerHIGH, jaY, jtkGreater, THRESHOLDDOWN, DELAY);
  jsc.registerAction(PIN, jamTriggerHIGH, DELAY);
  */
  /*
  jsc.registerAction(PINLEFT, jamTriggerLOW, jaX, jtkLess, THRESHOLDLEFT, DELAY, jmLeft);
  jsc.registerAction(PINRIGHT, jamTriggerLOW, jaX, jtkGreater, THRESHOLDRIGHT, DELAY, jmRight);
  jsc.registerAction(PINUP, jamTriggerLOW, jaY, jtkLess, THRESHOLDUP, DELAY, jmUp);
  jsc.registerAction(PINDOWN, jamTriggerLOW, jaY, jtkGreater, THRESHOLDDOWN, DELAY, jmDown);
  jsc.registerAction(PINFIRE, jamTriggerLOW, DELAY, jmFire);
  */
  jsc.registerAction(jamMappingInvers, jaX, jtkLess, THRESHOLDLEFT, DELAY, jmLeft);
  jsc.registerAction(jamMapping, jaX, jtkGreater, THRESHOLDRIGHT, DELAY, jmRight);
  jsc.registerAction(jamMappingInvers, jaY, jtkLess, THRESHOLDUP, DELAY, jmUp);
  jsc.registerAction(jamMapping, jaY, jtkGreater, THRESHOLDDOWN, DELAY, jmDown);
  jsc.initialize();
  observeMemory(0);
}

void loop() {
  jsc.processingLoop();
  if (jsc.hasLastMovement()) {
    if (LOGGING) {
      Serial.println(jsc.getLastMovement());
      observeMemory(0);
    }
  }
}

void joystickActionCallback(int id, joystickMovement joystickmovement) {
  Serial.print(id);
  Serial.print("->");
  Serial.println(joystickmovement);
}

void joystickActionValueCallback(int id, joystickMovement joystickmovement, int value) {
  Serial.print(id);
  Serial.print(" -> ");
  Serial.print(joystickmovement);
  Serial.print(" -> ");
  Serial.println(value);
}
