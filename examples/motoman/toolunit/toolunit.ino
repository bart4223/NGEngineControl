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
#define JOINTSHOULDERMAXSPEED 150
#define _JOINTELBOW           "Elbow"
#define JOINTELBOW            (char*)_JOINTELBOW
#define JOINTELBOWMINRAD      500
#define JOINTELBOWMAXRAD      870
#define JOINTELBOWMAXSPEED    150
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

void setup() {
    setGlobalUnit(&unitTool);
    unitTool.registerNotification(&serialNotification);
    #if (PROD == false)
    unitTool.registerNotification(&notificationLCD);
    unitTool.registerJoint(JOINTBASE, &jointBase, JOINTBASEMINRAD, JOINTBASEMAXRAD);
    #else
    unitTool.registerJoint(JOINTBASE, &jointBase, JOINTBASEMINRAD, JOINTBASEMAXRAD, JOINTBASEMAXMOVETICKS);
    #endif
    unitTool.registerJoint(JOINTSHOULDER, &jointShoulder, JOINTSHOULDERMINRAD, JOINTSHOULDERMAXRAD);
    unitTool.registerJoint(JOINTELBOW, &jointElbow, JOINTELBOWMINRAD, JOINTELBOWMAXRAD);
    unitTool.registerGripper(GRIPPER, &gripper, GRIPPERMINSPEED, GRIPPERMAXSPEED);
    unitTool.initialize();
    unitTool.jointSetMaxSpeed(JOINTSHOULDER, JOINTSHOULDERMAXSPEED);
    unitTool.jointSetMaxSpeed(JOINTELBOW, JOINTELBOWMAXSPEED);
    #if (PROD == false)
    unitTool.setWorkMode(wmSpec);
    #endif
    unitTool.clearInfo();
}

void loop() {
    unitTool.processingLoop();
}
