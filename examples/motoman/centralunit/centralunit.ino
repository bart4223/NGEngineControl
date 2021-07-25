#define PROD true //false,true
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
    unitCentral.registerComponent(ctJoint, TOOL, SHOULDER);
    unitCentral.registerComponent(ctJoint, TOOL, ELBOW);
    unitCentral.registerComponent(ctGripper, TOOL, GRIPPER);
    unitCentral.registerUnit(MOTION, MOTIONADDRESS);
    unitCentral.registerIRRemoteFunction(ftMenu, IRP_APPLE, IRA_APPLE, IRC_APPLE_MENU);
    unitCentral.registerIRRemoteFunction(ftLeft, IRP_APPLE, IRA_APPLE, IRC_APPLE_LEFT);
    unitCentral.registerIRRemoteFunction(ftRight, IRP_APPLE, IRA_APPLE, IRC_APPLE_RIGHT);
    unitCentral.registerIRRemoteFunction(ftUp, IRP_APPLE, IRA_APPLE, IRC_APPLE_UP);
    unitCentral.registerIRRemoteFunction(ftDown, IRP_APPLE, IRA_APPLE, IRC_APPLE_DOWN);
    unitCentral.registerIRRemoteFunction(ftOK, IRP_APPLE, IRA_APPLE, IRC_APPLE_OK);
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
