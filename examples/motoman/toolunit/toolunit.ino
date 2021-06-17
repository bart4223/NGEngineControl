#include <NGMemoryObserver.h>
#include <NGSerialNotification.h>
#include <NGUnitControl.h>

#define TOOL                  (char*)"Tool"
#define TOOLADDRESS           0x20
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

NGSerialNotification serialNotification = NGSerialNotification();
NGJointControl jointBase = NGJointControl(JOINT_0, ENGINE_3);
NGJointControl jointShoulder = NGJointControl(JOINT_1);
NGJointControl jointElbow = NGJointControl(JOINT_2);
NGGripperControl gripper = NGGripperControl(ENGINE_0);
NGUnitControl unitTool = NGUnitControl(TOOL);

enum workMode { wmNone, wmReadJointBase, wmMoveJointBase, wmSimulateJointBase, wmToggleGripper, wmReadJointShoulder, wmMoveJointShoulder, wmReadJointElbow, wmMoveJointElbow };

const workMode _workMode =  wmNone;
bool _gripperToggle = false;
 
void setup() {
  unitTool.registerNotification(&serialNotification);
  unitTool.registerJoint(JOINTBASE, &jointBase, JOINTBASEMINRAD, JOINTBASEMAXRAD, JOINTBASEMAXMOVETICKS);
  unitTool.registerJoint(JOINTSHOULDER, &jointShoulder, JOINTSHOULDERMINRAD, JOINTSHOULDERMAXRAD);
  unitTool.registerJoint(JOINTELBOW, &jointElbow, JOINTELBOWMINRAD, JOINTELBOWMAXRAD);
  unitTool.registerGripper(GRIPPER, &gripper, GRIPPERMINSPEED, GRIPPERMAXSPEED);
  unitTool.initialize();
  Serial.print("Current workMode is ");
  Serial.println(_workMode);
}

void loop() {
  switch (_workMode) {
    case wmNone:
      observeMemory(5000);
      break;
    case wmReadJointBase:
      unitTool.jointRead(JOINTBASE);
      observeMemory(1000);
      break;
    case wmMoveJointBase:
      moveJoint(JOINTBASE);
      observeMemory(0);
      break;
    case wmSimulateJointBase:
      unitTool.jointSimulate(JOINTBASE);
      break;
    case wmReadJointShoulder:
      unitTool.jointRead(JOINTSHOULDER);
      observeMemory(1000);
      break;
    case wmMoveJointShoulder:
      moveJoint(JOINTSHOULDER);
      observeMemory(0);
      break;
    case wmReadJointElbow:
      unitTool.jointRead(JOINTELBOW);
      observeMemory(1000);
      break;
    case wmMoveJointElbow:
      moveJoint(JOINTELBOW);
      observeMemory(0);
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
  }
  unitTool.processingLoop();
}

void moveJoint(char* name) {
  if (!unitTool.jointIsMoving(name)) {
    char log[100];
    sprintf(log, "Rotate joint %s to radiant = ", name);
    Serial.print(log);
    while (Serial.available() == 0);
    int targetRad = Serial.parseInt();
    Serial.read();
    Serial.println(targetRad);
    unitTool.jointMove(name, targetRad);
  }
}
