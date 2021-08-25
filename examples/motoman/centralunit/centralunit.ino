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
    int mpGripper = unitCentral.addMotionProfileComponent(mp, ctGripper, GRIPPER);
    int mpShoulder = unitCentral.addMotionProfileComponent(mp, ctJoint, SHOULDER);
    int mpElbow = unitCentral.addMotionProfileComponent(mp, ctJoint, ELBOW);
    int mpBase = unitCentral.addMotionProfileComponent(mp, ctJoint, BASE);
    // Dance - Sequence 00
    unitCentral.addMotionProfileComponentPosition(mpGripper, CGRIPPERRELEASE, 4000);
    unitCentral.addMotionProfileComponentPosition(mpShoulder, 600, 2000);
    unitCentral.addMotionProfileComponentPosition(mpElbow, 800, 2000);
    unitCentral.addMotionProfileComponentPosition(mpBase, 850, 3000);
    // Dance - Sequence 01
    unitCentral.addMotionProfileComponentPosition(mpGripper, CGRIPPERNONE);
    unitCentral.addMotionProfileComponentPosition(mpShoulder, 400, 2000);
    unitCentral.addMotionProfileComponentPosition(mpElbow, CJOINTPOSITIONNONE);
    unitCentral.addMotionProfileComponentPosition(mpBase, 750, 3000);
    // Dance - Sequence 02
    unitCentral.addMotionProfileComponentPosition(mpGripper, CGRIPPERNONE);
    unitCentral.addMotionProfileComponentPosition(mpShoulder, 600, 2000);
    unitCentral.addMotionProfileComponentPosition(mpElbow, 400, 2000);
    unitCentral.addMotionProfileComponentPosition(mpBase, CJOINTPOSITIONNONE);
    // Dance - Sequence 03
    unitCentral.addMotionProfileComponentPosition(mpGripper, CGRIPPERGRIP, 4000);
    unitCentral.addMotionProfileComponentPosition(mpShoulder, CJOINTPOSITIONNONE);
    unitCentral.addMotionProfileComponentPosition(mpElbow, CJOINTPOSITIONNONE);
    unitCentral.addMotionProfileComponentPosition(mpBase, CJOINTPOSITIONNONE);
    #endif
    #if (Dude == true)
    int mp = unitCentral.registerMotionProfile(DUDE, TOOL, false);
    int mpGripper = unitCentral.addMotionProfileComponent(mp, ctGripper, GRIPPER);
    int mpShoulder = unitCentral.addMotionProfileComponent(mp, ctJoint, SHOULDER);
    int mpElbow = unitCentral.addMotionProfileComponent(mp, ctJoint, ELBOW);
    int mpBase = unitCentral.addMotionProfileComponent(mp, ctJoint, BASE);
    // Dude - Sequence 00
    unitCentral.addMotionProfileComponentPosition(mpGripper, CGRIPPERNONE);
    unitCentral.addMotionProfileComponentPosition(mpShoulder, 600, 2000);
    unitCentral.addMotionProfileComponentPosition(mpElbow, 800, 2000);
    unitCentral.addMotionProfileComponentPosition(mpBase, 750, 3000);
    // Dude - Sequence 01
    unitCentral.addMotionProfileComponentPosition(mpGripper, CGRIPPERRELEASE, 4000);
    unitCentral.addMotionProfileComponentPosition(mpShoulder, 400, 2000);
    unitCentral.addMotionProfileComponentPosition(mpElbow, 600, 2000);
    unitCentral.addMotionProfileComponentPosition(mpBase, CJOINTPOSITIONNONE);
    // Dude - Sequence 02
    unitCentral.addMotionProfileComponentPosition(mpGripper, CGRIPPERGRIP, 4000);
    unitCentral.addMotionProfileComponentPosition(mpShoulder, 600, 2000);
    unitCentral.addMotionProfileComponentPosition(mpElbow, 800, 2000);
    unitCentral.addMotionProfileComponentPosition(mpBase, 850, 3000);
    // Dude - Sequence 03
    unitCentral.addMotionProfileComponentPosition(mpGripper, CGRIPPERNONE);
    unitCentral.addMotionProfileComponentPosition(mpShoulder, 400, 2000);
    unitCentral.addMotionProfileComponentPosition(mpElbow, 600, 2000);
    unitCentral.addMotionProfileComponentPosition(mpBase, CJOINTPOSITIONNONE);
    // Dude - Sequence 04
    unitCentral.addMotionProfileComponentPosition(mpGripper, CGRIPPERRELEASE, 4000);
    unitCentral.addMotionProfileComponentPosition(mpShoulder, 600, 2000);
    unitCentral.addMotionProfileComponentPosition(mpElbow, 800, 2000);
    unitCentral.addMotionProfileComponentPosition(mpBase, 800, 3000);
    // Dude - Sequence 05
    unitCentral.addMotionProfileComponentPosition(mpGripper, CGRIPPERGRIP, 4000);
    unitCentral.addMotionProfileComponentPosition(mpShoulder, 500, 2000);
    unitCentral.addMotionProfileComponentPosition(mpElbow, 700, 2000);
    unitCentral.addMotionProfileComponentPosition(mpBase, CJOINTPOSITIONNONE);
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
