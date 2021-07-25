#define PROD true //false,true
#if (PROD == false)
#include <NGLCDNotification.h>
#endif
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
#define LCDADDRESS            0x27
#define LCDCOLUMNS            16
#define LCDLINES              2

#if (PROD == false)
NGLCDNotification notificationLCD = NGLCDNotification(LCDADDRESS, LCDCOLUMNS, LCDLINES);
#endif
NGSerialNotification serialNotification = NGSerialNotification();
NGJointControl jointBase = NGJointControl(JOINT_0, ENGINE_3);
NGJointControl jointShoulder = NGJointControl(JOINT_1);
NGJointControl jointElbow = NGJointControl(JOINT_2);
NGGripperControl gripper = NGGripperControl(ENGINE_0);
NGUnitControl unitTool = NGUnitControl(TOOL, TOOLADDRESS);

enum workModeSpec { wmsGripper, wmsReadJointBase, wmsMoveJointBase, wmsReadJointShoulder, wmsMoveJointShoulder, wmsReadJointElbow, wmsMoveJointElbow };

workModeSpec _workModeSpec = wmsGripper;
 
void setup() {
    setGlobalUnit(&unitTool);
    unitTool.registerNotification(&serialNotification);
    #if (PROD == false)
    unitTool.registerNotification(&notificationLCD);
    #endif
    unitTool.registerJoint(JOINTBASE, &jointBase, JOINTBASEMINRAD, JOINTBASEMAXRAD, JOINTBASEMAXMOVETICKS);
    unitTool.registerJoint(JOINTSHOULDER, &jointShoulder, JOINTSHOULDERMINRAD, JOINTSHOULDERMAXRAD);
    unitTool.registerJoint(JOINTELBOW, &jointElbow, JOINTELBOWMINRAD, JOINTELBOWMAXRAD);
    unitTool.registerGripper(GRIPPER, &gripper, GRIPPERMINSPEED, GRIPPERMAXSPEED);
    unitTool.initialize();
    #if (PROD == false)
    unitTool.setWorkMode(wmMemoryObserver);
    #endif
    unitTool.clearInfo();
}

void loop() {
    if (unitTool.getWorkMode() == wmSpec) {
      switch (_workModeSpec) {
        case wmsReadJointBase:
          unitTool.jointRead(JOINTBASE);
          break;
        case wmsMoveJointBase:
          moveJoint(JOINTBASE);
          break;
        case wmsReadJointShoulder:
          unitTool.jointRead(JOINTSHOULDER);
          break;
        case wmsMoveJointShoulder:
          moveJoint(JOINTSHOULDER);
          break;
        case wmsReadJointElbow:
          unitTool.jointRead(JOINTELBOW);
          break;
        case wmsMoveJointElbow:
          moveJoint(JOINTELBOW);
          break;
        case wmsGripper:
          int readed = 0;
          byte input[10];
          while (Serial.available()) {
            input[readed] = Serial.read();
            if (input[readed] != '\n') {
              readed++;
            }
          }
          if (readed == 1) {
            if (input[0] == 0x67) { //g
              unitTool.gripperGrip(GRIPPER);
            } else if (input[0] == 0x72) { //r
              unitTool.gripperRelease(GRIPPER);
            }
          }
          break;
      }
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
