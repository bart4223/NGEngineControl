#include <NGMemoryObserver.h>
#include <NGJoystickControl.h>

#define LOGGING true // false

#define JOYSTICKID       0
#define JOYSTICKPINX    A8
#define JOYSTICKPINY    A9
#define JOYSTICKPINFIRE 14

#define PINUP     3
#define PINDOWN   4
#define PINLEFT   5
#define PINRIGHT  6
#define PINFIRE   7

#define DELAY 100

#define THRESHOLDUP       100
#define THRESHOLDDOWN     923
#define THRESHOLDLEFT     100
#define THRESHOLDRIGHT    923

NGJoystickControl jsc = NGJoystickControl(JOYSTICKID, JOYSTICKPINX, JOYSTICKPINY, JOYSTICKPINFIRE);

void setup() {
  Serial.begin(9600);
  jsc.setLogging(LOGGING);
  jsc.registerActionCallback(&joystickActionCallback);
  /*
  jsc.registerAction(PIN, jamTriggerHIGH, jaX, jtkLess, THRESHOLLEFT, DELAY);
  jsc.registerAction(PIN, jamTriggerHIGH, jaX, jtkGreater, THRESHOLDRIGHT, DELAY);
  jsc.registerAction(PIN, jamTriggerHIGH, jaY, jtkLess, THRESHOLDUP, DELAY);
  jsc.registerAction(PIN, jamTriggerHIGH, jaY, jtkGreater, THRESHOLDDOWN, DELAY);
  jsc.registerAction(PIN, jamTriggerHIGH, DELAY);
  */
  jsc.registerAction(PINLEFT, jamTriggerLOW, jaX, jtkLess, THRESHOLDLEFT, DELAY, jmLeft);
  jsc.registerAction(PINRIGHT, jamTriggerLOW, jaX, jtkGreater, THRESHOLDRIGHT, DELAY, jmRight);
  jsc.registerAction(PINUP, jamTriggerLOW, jaY, jtkLess, THRESHOLDUP, DELAY, jmUp);
  jsc.registerAction(PINDOWN, jamTriggerLOW, jaY, jtkGreater, THRESHOLDDOWN, DELAY, jmDown);
  jsc.registerAction(PINFIRE, jamTriggerLOW, DELAY, jmFire);
  jsc.initialize();
  observeMemory(0);
}

void loop() {
  jsc.processingLoop();
  if (jsc.hasLastMovement()) {
    Serial.println(jsc.getLastMovement());
    observeMemory(0);
  }
}

void joystickActionCallback(int id, joystickMovement joystickmovement) {
  Serial.print(id);
  Serial.print("->");
  Serial.println(joystickmovement);
}
