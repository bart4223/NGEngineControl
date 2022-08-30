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

NGJoystickControl ysc = NGJoystickControl(JOYSTICKID);

void setup() {
  Serial.begin(9600);
  ysc.setLogging(LOGGING);
  ysc.registerActionCallback(&joystickActionCallback);
  /*
  ysc.registerAction(PIN, jamTriggerHIGH, jaX, jtkLess, THRESHOLLEFT, DELAY);
  ysc.registerAction(PIN, jamTriggerHIGH, jaX, jtkGreater, THRESHOLDRIGHT, DELAY);
  ysc.registerAction(PIN, jamTriggerHIGH, jaY, jtkLess, THRESHOLDUP, DELAY);
  ysc.registerAction(PIN, jamTriggerHIGH, jaY, jtkGreater, THRESHOLDDOWN, DELAY);
  ysc.registerAction(PIN, jamTriggerHIGH, DELAY);
  */
  ysc.registerAction(PINLEFT, jamTriggerLOW, jaX, jtkLess, THRESHOLDLEFT, DELAY);
  ysc.registerAction(PINRIGHT, jamTriggerLOW, jaX, jtkGreater, THRESHOLDRIGHT, DELAY);
  ysc.registerAction(PINUP, jamTriggerLOW, jaY, jtkLess, THRESHOLDUP, DELAY);
  ysc.registerAction(PINDOWN, jamTriggerLOW, jaY, jtkGreater, THRESHOLDDOWN, DELAY);
  ysc.registerAction(PINFIRE, jamTriggerLOW, DELAY);
  ysc.initialize();
}

void loop() {
  ysc.processingLoop();
  //observeMemory(1000);
}

void joystickActionCallback(int id, joystickMovement joystickmovement) {
  Serial.print(id);
  Serial.print("->");
  Serial.println(joystickmovement);
}
