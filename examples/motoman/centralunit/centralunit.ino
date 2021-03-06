#define PROD true //false,true
#include <NGMemoryObserver.h>
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

#if (PROD == true)
NGLCDNotification notificationLCD = NGLCDNotification(LCDADDRESS, LCDCOLUMNS, LCDLINES);
#endif
NGSerialNotification notificationSerial = NGSerialNotification();
NGCentralUnitControl unitCentral = NGCentralUnitControl(CENTRAL);

enum workMode { wmNone, wmObserveMemory, wmCommand, wmCommandCyclic, wmCommandCyclicTwo, wmReceiveDataCyclic };

workMode _workMode = wmNone;
 
void setup() {
    char log[100];
    setGlobalUnit(&unitCentral);
    unitCentral.registerNotification(&notificationSerial);
    #if (PROD == true)
    unitCentral.registerNotification(&notificationLCD);
    #endif
    unitCentral.registerUnit(TOOL, TOOLADDRESS);
    unitCentral.registerUnit(MOTION, MOTIONADDRESS);
    unitCentral.initialize();
    unitCentral.clearInfo();
    sprintf(log, "Current workMode is %d", _workMode);
    unitCentral.writeInfo(log);
}

void loop() {
    switch (_workMode) {
      case wmNone:
        break;
      case wmObserveMemory:
        observeMemory(5000);
        break;
      case wmReceiveDataCyclic:
        unitCentral.receiveUnitData(MOTION);
        observeMemory(5000);
        break;
      case wmCommandCyclic:
        byte cmd[2];
        cmd[0] = 0x34; //4
        cmd[1] = 0x32; //2
        unitCentral.sendUnitCommand(MOTION, cmd, 2);
        observeMemory(5000);
        break;
      case wmCommandCyclicTwo:
        #if (PROD == true)
        unitCentral.sendUnitGripperGrip(TOOL, GRIPPER, GRIPPERSIZE);
        #else
        unitCentral.sendUnitGripperGrip(MOTION, GRIPPER, GRIPPERSIZE);
        #endif
        observeMemory(5000);
        break;
      case wmCommand:
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
        } else {
          observeMemory(5000);
        }
        break;
    }
    unitCentral.processingLoop();
}
