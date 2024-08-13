#define DIGITAL //ANALOG, DIGITAL

#include <NGMemoryObserver.h>
#include <NGJoystickControl.h>

#define LOGGING false // false

#define JOYSTICKID       0
#ifdef ANALOG
#define JOYSTICKPINX    A0
#define JOYSTICKPINY    A1
#endif
#ifdef DIGITAL
#define JOYSTICKPINXL    4
#define JOYSTICKPINXR    5
#define JOYSTICKPINYD    7
#define JOYSTICKPINYU    6
#endif
#define JOYSTICKPINFIRE  8

#define PINUP     3
#define PINDOWN   4
#define PINLEFT   5
#define PINRIGHT  6
#define PINFIRE   7

#define JOYSTICKDELAY 50

#ifdef ANALOG
#define THRESHOLDUP       510 // 100
#define THRESHOLDDOWN     530 // 923
#define THRESHOLDLEFT     516 // 100
#define THRESHOLDRIGHT    515 // 923
#endif
#ifdef DIGITAL
#define THRESHOLDUP       100
#define THRESHOLDDOWN     923
#define THRESHOLDLEFT     100
#define THRESHOLDRIGHT    923
#endif

#define CONTINOUSFIRETHRESHOLD 5

#ifdef ANALOG
NGJoystickControl jsc = NGJoystickControl(JOYSTICKID, JOYSTICKPINX, JOYSTICKPINY, JOYSTICKPINFIRE);
#endif
#ifdef DIGITAL
NGJoystickControl jsc = NGJoystickControl(JOYSTICKID, JOYSTICKPINXL, JOYSTICKPINXR, JOYSTICKPINYD, JOYSTICKPINYU, JOYSTICKPINFIRE);
#endif

void setup() {
  observeMemory(0);
  jsc.setLogging(LOGGING);
  //jsc.setLogXAxis(true);
  //jsc.setLogYAxis(true);
  jsc.setContinuousFireThreshold(CONTINOUSFIRETHRESHOLD);
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
  jsc.registerAction(jamMappingInvers, jaX, jtkLess, THRESHOLDLEFT, JOYSTICKDELAY, jmLeft);
  jsc.registerAction(jamMapping, jaX, jtkGreater, THRESHOLDRIGHT, JOYSTICKDELAY, jmRight);
  jsc.registerAction(jamMappingInvers, jaY, jtkLess, THRESHOLDUP, JOYSTICKDELAY, jmUp);
  jsc.registerAction(jamMapping, jaY, jtkGreater, THRESHOLDDOWN, JOYSTICKDELAY, jmDown);
  jsc.registerAction(PINFIRE, jamTriggerLOW, JOYSTICKDELAY, jmFire);
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
  Serial.print("id:");
  Serial.print(id);
  Serial.print(" -> ");
  switch(joystickmovement) {
    case jmFire:
      Serial.println("Fire");
      break;
  }
}

void joystickActionValueCallback(int id, joystickMovement joystickmovement, int value) {
  Serial.print("id:");
  Serial.print(id);
  Serial.print(" -> ");
  switch(joystickmovement) {
    case jmUp:
      Serial.print("Up");
      break;
    case jmDown:
      Serial.print("Down");
      break;
    case jmLeft:
      Serial.print("Left");
      break;
    case jmRight:
      Serial.print("Right");
      break;
  }
  Serial.print(" -> ");
  Serial.println(value);
}
