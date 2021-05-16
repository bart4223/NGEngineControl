#include <NGJointControl.h>

NGJointControl jointBase = NGJointControl(JOINT_0);

enum mode { None, ReadJointBase, MoveJointBase, SimulateJointBase };

const int _sleepJointRead = 500;
const mode _mode = None;
 
void setup() {
  jointBase.initialize((char*)"Base", 560, 1020);
  Serial.print("Current mode = ");
  Serial.println(_mode);
}

void loop() {
  int targetRad;
  char log[100];
  switch (_mode) {
    case ReadJointBase:
      jointBase.read();
      delay(_sleepJointRead);
      break;
    case MoveJointBase:
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
        jointBase.move(targetRad);
        unsigned long duration = millis() - start;
        sprintf(log, "...Rotation of joint %s end (duration: %d ms)", jointBase.getName(), duration);
        Serial.println(log);
      } else {
        sprintf(log, "Radiant of joint %s is invalid", jointBase.getName());
        Serial.println(log);
      }
      break;
    case SimulateJointBase:
      jointBase.simulate();
      break;
  }
}
