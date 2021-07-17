#define PROD true //false,true
#if (PROD == true)
#include <NGLCDNotification.h>
#endif
#include <NGSerialNotification.h>
#include <NGCentralUnitControl.h>

#define _CENTRAL      "Central"
#define CENTRAL       (char*)_CENTRAL
#define LCDADDRESS    0x27
#define LCDCOLUMNS    16
#define LCDLINES      2
#define _TOOL         "Tool"
#define TOOL          (char*)_TOOL
#define TOOLADDRESS   0x20
#define _MOTION       "Motion"
#define MOTION        (char*)_MOTION
#define MOTIONADDRESS 0x21

#define _GRIPPER    "Gripper"
#define GRIPPER     (char*)_GRIPPER
#define GRIPPERSIZE sizeof(_GRIPPER)
#define _ENGINE     "Engine"
#define ENGINE      (char*)_ENGINE
#define ENGINESIZE  sizeof(_ENGINE)

enum workModeSpec { wmsCommand, wmsCommandCyclic, wmsCommandCyclicTwo, wmsReceiveDataCyclic };
workModeSpec _workModeSpec = wmsCommand;

#if (PROD == true)
NGLCDNotification notificationLCD = NGLCDNotification(LCDADDRESS, LCDCOLUMNS, LCDLINES);
#endif
NGSerialNotification notificationSerial = NGSerialNotification();
NGCentralUnitControl unitCentral = NGCentralUnitControl(CENTRAL);

void setup() {
    setGlobalUnit(&unitCentral);
    unitCentral.registerNotification(&notificationSerial);
    #if (PROD == true)
    unitCentral.registerNotification(&notificationLCD);
    #endif
    unitCentral.registerUnit(TOOL, TOOLADDRESS);
    unitCentral.registerUnit(MOTION, MOTIONADDRESS);
    unitCentral.initialize();
    unitCentral.setWorkMode(wmNone);
    unitCentral.clearInfo();
}

void loop() {
    if (unitCentral.getWorkMode() == wmSpec) {
      switch (_workModeSpec) {
        case wmsReceiveDataCyclic:
          unitCentral.receiveUnitData(MOTION);
          break;
        case wmsCommandCyclic:
          byte cmd[2];
          cmd[0] = 0x34; //4
          cmd[1] = 0x32; //2
          unitCentral.sendUnitCommand(MOTION, cmd, 2);
          break;
        case wmsCommandCyclicTwo:
          #if (PROD == true)
          unitCentral.sendUnitGripperGrip(TOOL, GRIPPER, GRIPPERSIZE);
          #else
          unitCentral.sendUnitGripperGrip(MOTION, GRIPPER, GRIPPERSIZE);
          #endif
          break;
        case wmsCommand:
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
              #if (PROD == true)
              unitCentral.sendUnitGripperGrip(TOOL, GRIPPER, GRIPPERSIZE);
              #else
              unitCentral.sendUnitGripperGrip(MOTION, GRIPPER, GRIPPERSIZE);
              #endif
            } else if (input[0] == 0x72) { //r
              #if (PROD == true)
              unitCentral.sendUnitGripperRelease(TOOL, GRIPPER, GRIPPERSIZE);
              #else
              unitCentral.sendUnitGripperRelease(MOTION, GRIPPER, GRIPPERSIZE);
              #endif
            } else if (input[0] == 0x73) { //s
              unitCentral.sendUnitEngineSetSpeed(MOTION, ENGINE, ENGINESIZE, 42);
            } else {
              unitCentral.sendUnitCommand(MOTION, input, readed);
            }
          } else if (readed > 1) {
            unitCentral.sendUnitCommand(MOTION, input, readed);
          }
          break;
      }
    }
    unitCentral.processingLoop();
}
