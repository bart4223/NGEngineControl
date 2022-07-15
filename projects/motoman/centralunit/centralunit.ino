#define PROD  true  //false,true
#define Dance true  //false,true
#define Dude  true  //false,true
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
    int mpDance = unitCentral.registerMotionProfile(DANCE, TOOL);
    int mpcDanceGripper = unitCentral.addMotionProfileComponent(mpDance, ctGripper, GRIPPER);
    int mpcDanceShoulder = unitCentral.addMotionProfileComponent(mpDance, ctJoint, SHOULDER);
    int mpcDanceElbow = unitCentral.addMotionProfileComponent(mpDance, ctJoint, ELBOW);
    int mpcDanceBase = unitCentral.addMotionProfileComponent(mpDance, ctJoint, BASE);
    unitCentral.addMotionProfileItem(mpDance, mpcDanceGripper, CGRIPPERRELEASE, 4000);
    unitCentral.addMotionProfileItem(mpDance, mpcDanceShoulder, 600, 2000);
    unitCentral.addMotionProfileItem(mpDance, mpcDanceElbow, 800, 2000);
    unitCentral.addMotionProfileItem(mpDance, mpcDanceBase, 850, 3000);
    unitCentral.addMotionProfileItem(mpDance, mpcDanceShoulder, 400, 2000);
    unitCentral.addMotionProfileItem(mpDance, mpcDanceBase, 750, 3000);
    unitCentral.addMotionProfileItem(mpDance, mpcDanceShoulder, 600, 2000);
    unitCentral.addMotionProfileItem(mpDance, mpcDanceElbow, 400, 2000);
    unitCentral.addMotionProfileItem(mpDance, mpcDanceGripper, CGRIPPERGRIP, 4000);
    #endif
    #if (Dude == true)
    int mpDude = unitCentral.registerMotionProfile(DUDE, TOOL, false);
    int mpcDudeGripper = unitCentral.addMotionProfileComponent(mpDude, ctGripper, GRIPPER);
    int mpcDudeShoulder = unitCentral.addMotionProfileComponent(mpDude, ctJoint, SHOULDER);
    int mpcDudeElbow = unitCentral.addMotionProfileComponent(mpDude, ctJoint, ELBOW);
    int mpcDudeBase = unitCentral.addMotionProfileComponent(mpDude, ctJoint, BASE);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeShoulder, 600, 2000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeElbow, 800, 2000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeBase, 750, 3000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeGripper, CGRIPPERRELEASE, 4000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeShoulder, 400, 2000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeElbow, 600, 2000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeGripper, CGRIPPERGRIP, 4000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeShoulder, 600, 2000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeElbow, 800, 2000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeBase, 850, 3000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeShoulder, 400, 2000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeElbow, 600, 2000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeGripper, CGRIPPERRELEASE, 4000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeShoulder, 600, 2000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeElbow, 800, 2000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeBase, 800, 3000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeGripper, CGRIPPERGRIP, 4000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeShoulder, 500, 2000);
    unitCentral.addMotionProfileItem(mpDude, mpcDudeElbow, 700, 2000);
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
