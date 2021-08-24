#define PROD true //false,true
#include <NGSerialNotification.h>
#include <NGUnitControl.h>

#define _TOOL         "Tool"
#define TOOL          (char*)_TOOL
#define TOOLADDRESS   0x20

#define _JOINTBASE                        "Base"
#define JOINTBASE                         (char*)_JOINTBASE
#define JOINTBASEMINRAD                   600
#define JOINTBASEMAXRAD                   1000
#define JOINTBASEMAXMOVETICKS             20

#define _JOINTSHOULDER                    "Shoulder"
#define JOINTSHOULDER                     (char*)_JOINTSHOULDER
#define JOINTSHOULDERMINRAD               350 //down
#define JOINTSHOULDERMAXRAD               600 //up
#define JOINTSHOULDERMAXSPEED             150
#define JOINTSHOULDERTRANSDUCERTHRESHOLD  10
#define JOINTSHOULDERMOVESTEP             30

#define _JOINTELBOW                       "Elbow"
#define JOINTELBOW                        (char*)_JOINTELBOW
#define JOINTELBOWMINRAD                  300 //down
#define JOINTELBOWMAXRAD                  900 //up
#define JOINTELBOWMAXSPEED                150
#define JOINTELBOWTRANSDUCERTHRESHOLD     10
#define JOINTELBOWMOVESTEP                30

#define _GRIPPER            "Gripper"
#define GRIPPER             (char*)_GRIPPER
#define GRIPPERMINSPEED     60
#define GRIPPERMAXSPEED     150

#define _COMMANDJOINTSIMULATEBASE     "b"
#define COMMANDJOINTSIMULATEBASE      (char*)_COMMANDJOINTSIMULATEBASE
#define _COMMANDJOINTSIMULATESHOULDER "s"
#define COMMANDJOINTSIMULATESHOULDER  (char*)_COMMANDJOINTSIMULATESHOULDER
#define _COMMANDJOINTSIMULATEELBOW    "e"
#define COMMANDJOINTSIMULATEELBOW     (char*)_COMMANDJOINTSIMULATEELBOW
#define _COMMANDGRIPPERSIMULATE       "g"
#define COMMANDGRIPPERSIMULATE        (char*)_COMMANDGRIPPERSIMULATE

NGSerialNotification serialNotification = NGSerialNotification();
NGJointControl jointBase = NGJointControl(JOINT_0, ENGINE_3);
NGJointControl jointShoulder = NGJointControl(JOINT_1);
NGJointControl jointElbow = NGJointControl(JOINT_2);
NGGripperControl gripper = NGGripperControl(ENGINE_0);
NGUnitControl unitTool = NGUnitControl(TOOL, TOOLADDRESS);

void setup() {
    setGlobalUnit(&unitTool);
    unitTool.registerNotification(&serialNotification);
    unitTool.registerJoint(JOINTBASE, &jointBase, JOINTBASEMINRAD, JOINTBASEMAXRAD);
    unitTool.registerJoint(JOINTSHOULDER, &jointShoulder, JOINTSHOULDERMINRAD, JOINTSHOULDERMAXRAD, DEFAULTMAXMOVETICKS, DEFAULTENGINE, JOINTSHOULDERMOVESTEP);
    unitTool.registerJoint(JOINTELBOW, &jointElbow, JOINTELBOWMINRAD, JOINTELBOWMAXRAD, DEFAULTMAXMOVETICKS, DEFAULTENGINE, JOINTELBOWMOVESTEP);
    unitTool.registerGripper(GRIPPER, &gripper, GRIPPERMINSPEED, GRIPPERMAXSPEED);
    unitTool.initialize();
    unitTool.jointSetMaxSpeed(JOINTSHOULDER, JOINTSHOULDERMAXSPEED);
    unitTool.jointSetTransducerThreshold(JOINTSHOULDER, JOINTSHOULDERTRANSDUCERTHRESHOLD);
    unitTool.jointSetMaxSpeed(JOINTELBOW, JOINTELBOWMAXSPEED);
    unitTool.jointSetTransducerThreshold(JOINTELBOW, JOINTELBOWTRANSDUCERTHRESHOLD);
    #if (PROD == false)
    unitTool.registerCommand(COMMANDJOINTSIMULATEBASE, ckJointSimulate, JOINTBASE);
    unitTool.registerCommand(COMMANDJOINTSIMULATESHOULDER, ckJointSimulate, JOINTSHOULDER);
    unitTool.registerCommand(COMMANDJOINTSIMULATEELBOW, ckJointSimulate, JOINTELBOW);
    unitTool.registerCommand(COMMANDGRIPPERSIMULATE, ckGripperSimulate, GRIPPER);
    unitTool.setWorkMode(wmCommand);
    #endif
    unitTool.jointMoveZero(JOINTBASE);
    unitTool.jointMoveZero(JOINTSHOULDER);
    unitTool.jointMoveZero(JOINTELBOW);
}

void loop() {
    unitTool.processingLoop();
}
