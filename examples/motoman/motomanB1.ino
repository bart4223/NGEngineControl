#include <NGJointControl.h>

NGJointControl jointBase = NGJointControl(JOINT_0, ENGINE_3);

enum workMode { wmNone, wmReadJointBase, wmMoveJointBase, wmSimulateJointBase };

const int _sleepJointRead = 500;
const workMode _workMode = wmNone;
 
void setup() {
  jointBase.initialize((char*)"Base", 560, 1020);
  Serial.print("Current workMode = ");
  Serial.println(_workMode);
}

void loop() {
  int targetRad;
  char log[100];
  switch (_workMode) {
    case wmReadJointBase:
      jointBase.read();
      delay(_sleepJointRead);
      break;
    case wmMoveJointBase:
      sprintf(log, "Rotate joint %s to radiant = ", jointBase.getName());
      Serial.print(log);
      while (Serial.available() == 0);
      targetRad = Serial.parseInt();
      Serial.read();
      Serial.println(targetRad);
      if (targetRad >= jointBase.getMinJointRad() && targetRad <= jointBase.getMaxJointRad()) {
        sprintf(log, "Rotation of joint %2 start...", jointBase.getName());
        Serial.println(log);
        unsigned long start = millis();
        bool reached = jointBase.move(targetRad);
        unsigned long duration = millis() - start;
        if (reached) {
          sprintf(log, "...Rotation of joint %s end (duration: %d ms)...target reached", jointBase.getName(), duration);
        } else {
          sprintf(log, "...Rotation of joint %s end (duration: %d ms)...target NOT reached", jointBase.getName(), duration);
        }
        Serial.println(log);
      } else {
        sprintf(log, "Radiant of joint %s is invalid", jointBase.getName());
        Serial.println(log);
      }
      break;
    case wmSimulateJointBase:
      jointBase.simulate();
      break;
  }
}
