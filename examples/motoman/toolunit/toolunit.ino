#include <NGUnitControl.h>
#include <NGMemoryObserver.h>

#define TOOL                  (char*)"Tool"
#define JOINTBASE             (char*)"Base"
#define JOINTBASEMINRAD       560
#define JOINTBASEMAXRAD       1020
#define JOINTBASEMAXMOVETICKS 20
#define JOINTSHOULDER         (char*)"Shoulder"
#define JOINTSHOULDERMINRAD   550
#define JOINTSHOULDERMAXRAD   800
#define JOINTELBOW            (char*)"Elbow"
#define JOINTELBOWMINRAD      500
#define JOINTELBOWMAXRAD      870
#define GRIPPER               (char*)"Gripper"
#define GRIPPERMINSPEED       60
#define GRIPPERMAXSPEED       150

NGJointControl jointBase = NGJointControl(JOINT_0, ENGINE_3);
NGJointControl jointShoulder = NGJointControl(JOINT_1);
NGJointControl jointElbow = NGJointControl(JOINT_2);
NGGripperControl gripper = NGGripperControl(ENGINE_0);
NGUnitControl unitTool = NGUnitControl(TOOL);

enum workMode { wmNone, wmReadJointBase, wmMoveJointBase, wmSimulateJointBase, wmToggleGripper, wmReadJointElbow, wmReadJointShoulder };

const int _sleepJointRead = 1000;
const workMode _workMode =  wmNone;
bool _reached = true;
int _targetRad;
unsigned long _start;
bool _gripperToggle = false;
 
void setup() {
  unitTool.registerJoint(JOINTBASE, &jointBase, JOINTBASEMINRAD, JOINTBASEMAXRAD, JOINTBASEMAXMOVETICKS);
  unitTool.registerJoint(JOINTSHOULDER, &jointShoulder, JOINTSHOULDERMINRAD, JOINTSHOULDERMAXRAD);
  unitTool.registerJoint(JOINTELBOW, &jointElbow, JOINTELBOWMINRAD, JOINTELBOWMAXRAD);
  unitTool.registerGripper(GRIPPER, &gripper, GRIPPERMINSPEED, GRIPPERMAXSPEED);
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
      unitTool.jointRead(JOINTBASE);
      observeMemory(_sleepJointRead);
      break;
    case wmReadJointShoulder:
      unitTool.jointRead(JOINTSHOULDER);
      observeMemory(_sleepJointRead);
      break;
    case wmReadJointElbow:
      unitTool.jointRead(JOINTELBOW);
      observeMemory(_sleepJointRead);
      break;
    case wmToggleGripper:
      if (_gripperToggle) {
          unitTool.gripperGrip(GRIPPER);
      } else {
          unitTool.gripperRelease(GRIPPER);
      }
      _gripperToggle = !_gripperToggle;
      observeMemory(3000);
      break;
    case wmMoveJointBase:
      observeMemory(0);
      if (!_reached) {
          _reached = unitTool.jointMove(JOINTBASE, _targetRad);
          if (_reached) {
            unsigned long duration = millis() - _start;
            sprintf(log, "...Rotation of joint %s end (duration: %d ms)...target reached", JOINTBASE, duration);
            Serial.println(log);
          }
      } else {
        sprintf(log, "Rotate joint %s to radiant = ", JOINTBASE);
        Serial.print(log);
        while (Serial.available() == 0);
        _targetRad = Serial.parseInt();
        Serial.read();
        Serial.println(_targetRad);
        if (_targetRad >= JOINTBASEMINRAD && _targetRad <= JOINTBASEMAXRAD) {
          sprintf(log, "Rotation of joint %2 start...", JOINTBASE);
          Serial.println(log);
          _start = millis();
          _reached = unitTool.jointMove(JOINTBASE, _targetRad);
        } else {
          sprintf(log, "Radiant of joint %s is invalid", JOINTBASE);
          Serial.println(log);
        }
      }
      break;
    case wmSimulateJointBase:
      unitTool.jointSimulate(JOINTBASE);
      break;
  }
}
