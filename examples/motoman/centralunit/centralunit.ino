#include <NGMemoryObserver.h>
//#include <NGLCDNotification.h>
#include <NGSerialNotification.h>
#include <NGCentralUnitControl.h>

#define CENTRAL       (char*)"Central"
#define LCDADDRESS    0x27
#define LCDCOLUMNS    16
#define LCDLINES      2
#define TOOL          (char*)"Tool"
#define TOOLADDRESS   0x20
#define MOTION        (char*)"Motion"
#define MOTIONADDRESS 0x21

#define GRIPPER       (char*)"Gripper"
#define GRIPPERSIZE   sizeof("Gripper")

//NGLCDNotification notificationLCD = NGLCDNotification(LCDADDRESS, LCDCOLUMNS, LCDLINES);
NGSerialNotification notificationSerial = NGSerialNotification();
NGCentralUnitControl unitCentral = NGCentralUnitControl(CENTRAL);

enum workMode { wmNone, wmMotionCommand, wmMotionCommandCyclic, wmMotionReceiveDataCyclic };

workMode _workMode = wmNone;
 
void setup() {
    setGlobalUnit(&unitCentral);
    unitCentral.registerNotification(&notificationSerial);
    //unitCentral.registerNotification(&notificationLCD);
    unitCentral.registerUnit(TOOL, TOOLADDRESS);
    unitCentral.registerUnit(MOTION, MOTIONADDRESS);
    unitCentral.initialize();
    Serial.print("Current workMode is ");
    Serial.println(_workMode);
}

void loop() {
    switch (_workMode) {
    case wmNone:
      observeMemory(5000);
      break;
    case wmMotionReceiveDataCyclic:
      unitCentral.receiveUnitData(MOTION);
      observeMemory(5000);
      break;
    case wmMotionCommandCyclic:
      byte cmd[2];
      cmd[0] = 0x34; //4
      cmd[1] = 0x32; //2
      unitCentral.sendUnitCommand(MOTION, cmd, 2);
      observeMemory(5000);
      break;
    case wmMotionCommand:
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
          unitCentral.sendUnitGripperGrip(MOTION, GRIPPER, GRIPPERSIZE);
        } else if (input[0] == 0x72) { //r
          unitCentral.sendUnitGripperRelease(MOTION, GRIPPER, GRIPPERSIZE);
        } else {
          unitCentral.sendUnitCommand(MOTION, input, readed);
        }
      } else if (readed > 1) {
        unitCentral.sendUnitCommand(MOTION, input, readed);
      }
      observeMemory(5000);
      break;
    }
    unitCentral.processingLoop();
}
