#include <NGMemoryObserver.h>
#include <NGJoystickControl.h>

#define LOGGING true // false

#define JOYSTICKID 0

#define PINUP     3
#define PINDOWN   4
#define PINLEFT   5
#define PINRIGHT  6
#define PINFIRE   3

#define DELAY 500

#define THRESHOLDUP       100
#define THRESHOLDDOWN     923
#define THRESHOLDLEFT     100
#define THRESHOLDRIGHT    923

NGJoystickControl jsc = NGJoystickControl(JOYSTICKID);

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
  jsc.registerAction(PINFIRE, jamTriggerLOW, DELAY);
  jsc.initialize();
}

void loop() {
  jsc.processingLoop();
  if (jsc.hasLastMovement()) {
    Serial.println(jsc.getLastMovement());
  }
  //observeMemory(1000);
}

void joystickActionCallback(int id, joystickMovement joystickmovement) {
  Serial.print(id);
  Serial.print("->");
  Serial.println(joystickmovement);
}
