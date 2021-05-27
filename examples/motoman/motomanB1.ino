#include <NGJointControl.h>

NGJointControl jointBase = NGJointControl(JOINT_0, ENGINE_3);

enum workMode { wmNone, wmReadJointBase, wmMoveJointBase, wmSimulateJointBase };

const int _sleepJointRead = 500;
const workMode _workMode = wmNone;
bool _reached = true;
int _targetRad;
unsigned long _start;
 
void setup() {
  jointBase.initialize((char*)"Base", 560, 1020);
  jointBase.setMaxMoveTicks(10);
  Serial.print("Current workMode = ");
  Serial.println(_workMode);
}

void loop() {
  char log[100];
  switch (_workMode) {
    case wmReadJointBase:
      jointBase.read();
      delay(_sleepJointRead);
      break;
    case wmMoveJointBase:
      if (!_reached) {
          _reached = jointBase.move(_targetRad);
          if (_reached) {
            unsigned long duration = millis() - _start;
            sprintf(log, "...Rotation of joint %s end (duration: %d ms)...target reached", jointBase.getName(), duration);
            Serial.println(log);
          }
      } else {
        sprintf(log, "Rotate joint %s to radiant = ", jointBase.getName());
        Serial.print(log);
        while (Serial.available() == 0);
        _targetRad = Serial.parseInt();
        Serial.read();
        Serial.println(_targetRad);
        if (_targetRad >= jointBase.getMinJointRad() && _targetRad <= jointBase.getMaxJointRad()) {
          sprintf(log, "Rotation of joint %2 start...", jointBase.getName());
          Serial.println(log);
          _start = millis();
          _reached = jointBase.move(_targetRad);
        } else {
          sprintf(log, "Radiant of joint %s is invalid", jointBase.getName());
          Serial.println(log);
        }
      }
      break;
    case wmSimulateJointBase:
      jointBase.simulate();
      break;
  }
}
