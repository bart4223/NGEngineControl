#include <NGUnitControl.h>
#include <NGMemoryObserver.h>

NGJointControl jointBase = NGJointControl(JOINT_0, ENGINE_3);
NGJointControl jointShoulder = NGJointControl(JOINT_1);
NGJointControl jointElbow = NGJointControl(JOINT_2);
NGGripperControl gripper = NGGripperControl(ENGINE_0);
NGUnitControl unitTool = NGUnitControl((char*)"Tool");

enum workMode { wmNone, wmReadJointBase, wmMoveJointBase, wmSimulateJointBase, wmToggleGripper, wmReadJointElbow, wmReadJointShoulder };

const int _sleepJointRead = 1000;
const workMode _workMode = wmNone;
bool _reached = true;
int _targetRad;
unsigned long _start;
bool _gripperToggle = false;
 
void setup() {
  jointBase.initialize((char*)"Base", 560, 1020);
  jointBase.setMaxMoveTicks(20);
  //unitTool.registerJoint((char*)"Base", JOINT_0, ENGINE_3, 550, 800);
  unitTool.registerJoint((char*)"Shoulder", &jointShoulder, 550, 800);
  unitTool.registerJoint((char*)"Elbow", &jointElbow, 500, 870);
  unitTool.registerGripper((char*)"Gripper", &gripper, 60, 150);
  unitTool.initialize();
  Serial.print("Current workMode is ");
  Serial.println(_workMode);
}

void loop() {
  char log[100];
  switch (_workMode) {
    case wmNone:
      observeMemory(5000);
      break;
    case wmReadJointBase:
      jointBase.read();
      observeMemory(_sleepJointRead);
      break;
    case wmReadJointShoulder:
      unitTool.jointRead((char*)"Shoulder");
      observeMemory(_sleepJointRead);
      break;
    case wmReadJointElbow:
      unitTool.jointRead((char*)"Elbow");
      observeMemory(_sleepJointRead);
      break;
    case wmToggleGripper:
      if (_gripperToggle) {
          unitTool.gripperGrip((char*)"Gripper");
      } else {
          unitTool.gripperRelease((char*)"Gripper");
      }
      _gripperToggle = !_gripperToggle;
      observeMemory(3000);
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
