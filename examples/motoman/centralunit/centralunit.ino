#define PROD  true  //false,true
#define Dance true  //false,true
#define Dude  false //false,true
#if (PROD == true)
#include <NGLCDNotification.h>
#endif
#include <IRremote.h>
#include <NGSerialNotification.h>
#include <NGCentralUnitControl.h>

#define _CENTRAL      "Central"
#define CENTRAL       (char*)_CENTRAL
#define _TOOL         "Tool"
#define TOOL          (char*)_TOOL
#define TOOLADDRESS   0x20
#define _MOTION       "Motion"
#define MOTION        (char*)_MOTION
#define MOTIONADDRESS 0x21

#define LCDADDRESS    0x27
#define LCDCOLUMNS    16
#define LCDLINES      2

#define _BASE       "Base"
#define BASE        (char*)_BASE
#define _SHOULDER   "Shoulder"
#define SHOULDER    (char*)_SHOULDER
#define _ELBOW      "Elbow"
#define ELBOW       (char*)_ELBOW
#define _GRIPPER    "Gripper"
#define GRIPPER     (char*)_GRIPPER

#define SHOULDERSTEPWIDTH 30
#define ELBOWSTEPWIDTH    30

#define _DANCE  "Dance"
#define DANCE   (char*)_DANCE

#define _DUDE  "Dude"
#define DUDE   (char*)_DUDE

#define IRREMOTE    11

#if (PROD == true)
NGLCDNotification notificationLCD = NGLCDNotification(LCDADDRESS, LCDCOLUMNS, LCDLINES);
#endif
NGSerialNotification notificationSerial = NGSerialNotification();
NGCentralUnitControl unitCentral = NGCentralUnitControl(CENTRAL);
IRrecv _irrecv(IRREMOTE);

void setup() {
    _irrecv.enableIRIn();
    setGlobalUnit(&unitCentral);
    unitCentral.registerNotification(&notificationSerial);
    #if (PROD == true)
    unitCentral.registerNotification(&notificationLCD);
    #endif
    unitCentral.registerUnit(TOOL, TOOLADDRESS);
    unitCentral.registerComponent(ctJoint, TOOL, BASE);
    unitCentral.registerComponent(ctJoint, TOOL, SHOULDER, SHOULDERSTEPWIDTH);
    unitCentral.registerComponent(ctJoint, TOOL, ELBOW, ELBOWSTEPWIDTH);
    unitCentral.registerComponent(ctGripper, TOOL, GRIPPER);
    #if (Dance == true)
    int mp = unitCentral.registerMotionProfile(DANCE, TOOL);
    int mpcGripper = unitCentral.addMotionProfileComponent(mp, ctGripper, GRIPPER);
    int mpcShoulder = unitCentral.addMotionProfileComponent(mp, ctJoint, SHOULDER);
    int mpcElbow = unitCentral.addMotionProfileComponent(mp, ctJoint, ELBOW);
    int mpcBase = unitCentral.addMotionProfileComponent(mp, ctJoint, BASE);
    unitCentral.addMotionProfileItem(mp, mpcGripper, CGRIPPERRELEASE, 4000);
    unitCentral.addMotionProfileItem(mp, mpcShoulder, 600, 2000);
    unitCentral.addMotionProfileItem(mp, mpcElbow, 800, 2000);
    unitCentral.addMotionProfileItem(mp, mpcBase, 850, 3000);
    unitCentral.addMotionProfileItem(mp, mpcShoulder, 400, 2000);
    unitCentral.addMotionProfileItem(mp, mpcBase, 750, 3000);
    unitCentral.addMotionProfileItem(mp, mpcShoulder, 600, 2000);
    unitCentral.addMotionProfileItem(mp, mpcElbow, 400, 2000);
    unitCentral.addMotionProfileItem(mp, mpcGripper, CGRIPPERGRIP, 4000);
    #endif
    #if (Dude == true)
    int mp = unitCentral.registerMotionProfile(DUDE, TOOL, false);
    int mpcGripper = unitCentral.addMotionProfileComponent(mp, ctGripper, GRIPPER);
    int mpcShoulder = unitCentral.addMotionProfileComponent(mp, ctJoint, SHOULDER);
    int mpcElbow = unitCentral.addMotionProfileComponent(mp, ctJoint, ELBOW);
    int mpcBase = unitCentral.addMotionProfileComponent(mp, ctJoint, BASE);
    unitCentral.addMotionProfileItem(mp, mpcShoulder, 600, 2000);
    unitCentral.addMotionProfileItem(mp, mpcElbow, 800, 2000);
    unitCentral.addMotionProfileItem(mp, mpcBase, 750, 3000);
    unitCentral.addMotionProfileItem(mp, mpcGripper, CGRIPPERRELEASE, 4000);
    unitCentral.addMotionProfileItem(mp, mpcShoulder, 400, 2000);
    unitCentral.addMotionProfileItem(mp, mpcElbow, 600, 2000);
    unitCentral.addMotionProfileItem(mp, mpcGripper, CGRIPPERGRIP, 4000);
    unitCentral.addMotionProfileItem(mp, mpcShoulder, 600, 2000);
    unitCentral.addMotionProfileItem(mp, mpcElbow, 800, 2000);
    unitCentral.addMotionProfileItem(mp, mpcBase, 850, 3000);
    unitCentral.addMotionProfileItem(mp, mpcShoulder, 400, 2000);
    unitCentral.addMotionProfileItem(mp, mpcElbow, 600, 2000);
    unitCentral.addMotionProfileItem(mp, mpcGripper, CGRIPPERRELEASE, 4000);
    unitCentral.addMotionProfileItem(mp, mpcShoulder, 600, 2000);
    unitCentral.addMotionProfileItem(mp, mpcElbow, 800, 2000);
    unitCentral.addMotionProfileItem(mp, mpcBase, 800, 3000);
    unitCentral.addMotionProfileItem(mp, mpcGripper, CGRIPPERGRIP, 4000);
    unitCentral.addMotionProfileItem(mp, mpcShoulder, 500, 2000);
    unitCentral.addMotionProfileItem(mp, mpcElbow, 700, 2000);
    #endif
    unitCentral.registerUnit(MOTION, MOTIONADDRESS);
    unitCentral.registerIRRemoteFunction(ftMenu, IRP_APPLE, IRA_APPLE, IRC_APPLE_MENU);
    unitCentral.registerIRRemoteFunction(ftLeft, IRP_APPLE, IRA_APPLE, IRC_APPLE_LEFT);
    unitCentral.registerIRRemoteFunction(ftRight, IRP_APPLE, IRA_APPLE, IRC_APPLE_RIGHT);
    unitCentral.registerIRRemoteFunction(ftUp, IRP_APPLE, IRA_APPLE, IRC_APPLE_UP);
    unitCentral.registerIRRemoteFunction(ftDown, IRP_APPLE, IRA_APPLE, IRC_APPLE_DOWN);
    unitCentral.registerIRRemoteFunction(ftOK, IRP_APPLE, IRA_APPLE, IRC_APPLE_OK);
    unitCentral.registerIRRemoteFunction(ftPlay, IRP_APPLE, IRA_APPLE, IRC_APPLE_PLAY);
    unitCentral.initialize();
    #if (PROD == false)
    unitCentral.setWorkMode(wmObserveMemory);
    #endif
    unitCentral.clearInfo();
}

void loop() {
    if (_irrecv.decode()) {
      unitCentral.setIRRemoteData(_irrecv.decodedIRData.protocol,_irrecv.decodedIRData.address,_irrecv.decodedIRData.command);
      _irrecv.resume();
    }
    unitCentral.processingLoop();
}
