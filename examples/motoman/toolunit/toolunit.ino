#define PROD true //false,true
#include <NGMemoryObserver.h>
#include <NGSerialNotification.h>
#include <NGUnitControl.h>

#define _TOOL                 "Tool"
#define TOOL                  (char*)_TOOL
#define TOOLADDRESS           0x20
#define _JOINTBASE            "Base"
#define JOINTBASE             (char*)_JOINTBASE
#define JOINTBASEMINRAD       560
#define JOINTBASEMAXRAD       1020
#define JOINTBASEMAXMOVETICKS 20
#define _JOINTSHOULDER        "Shoulder"
#define JOINTSHOULDER         (char*)_JOINTSHOULDER
#define JOINTSHOULDERMINRAD   550
#define JOINTSHOULDERMAXRAD   800
#define _JOINTELBOW           "Elbow"
#define JOINTELBOW            (char*)_JOINTELBOW
#define JOINTELBOWMINRAD      500
#define JOINTELBOWMAXRAD      870
#define _GRIPPER              "Gripper"
#define GRIPPER               (char*)_GRIPPER
#define GRIPPERMINSPEED       60
#define GRIPPERMAXSPEED       150

NGSerialNotification serialNotification = NGSerialNotification();
NGJointControl jointBase = NGJointControl(JOINT_0, ENGINE_3);
NGJointControl jointShoulder = NGJointControl(JOINT_1);
NGJointControl jointElbow = NGJointControl(JOINT_2);
NGGripperControl gripper = NGGripperControl(ENGINE_0);
NGUnitControl unitTool = NGUnitControl(TOOL, TOOLADDRESS);

enum workMode { wmNone, wmObserveMemory, wmReadJointBase, wmMoveJointBase, wmSimulateJointBase, wmToggleGripper, wmReadJointShoulder, wmMoveJointShoulder, wmReadJointElbow, wmMoveJointElbow };

const workMode _workMode =  wmNone;
bool _gripperToggle = false;
 
void setup() {
    char log[100];
    setGlobalUnit(&unitTool);
    unitTool.registerNotification(&serialNotification);
    unitTool.registerJoint(JOINTBASE, &jointBase, JOINTBASEMINRAD, JOINTBASEMAXRAD, JOINTBASEMAXMOVETICKS);
    unitTool.registerJoint(JOINTSHOULDER, &jointShoulder, JOINTSHOULDERMINRAD, JOINTSHOULDERMAXRAD);
    unitTool.registerJoint(JOINTELBOW, &jointElbow, JOINTELBOWMINRAD, JOINTELBOWMAXRAD);
    unitTool.registerGripper(GRIPPER, &gripper, GRIPPERMINSPEED, GRIPPERMAXSPEED);
    unitTool.initialize();
    sprintf(log, "Current workMode is %d", _workMode);
    unitTool.writeInfo(log);
}

void loop() {
    switch (_workMode) {
      case wmNone:
        break;
      case wmObserveMemory:
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
