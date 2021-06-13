#include <NGMemoryObserver.h>
//#include <NGLCDNotification.h>
#include <NGSerialNotification.h>
#include <NGCentralUnitControl.h>

#define CENTRAL       (char*)"Central"
#define LCDADDRESS    0x27
#define TOOL          (char*)"Tool"
#define TOOLADDRESS   0x08
#define MOTION        (char*)"Motion"
#define MOTIONADDRESS 0x09

//NGLCDNotification notificationLCD = NGLCDNotification(LCDADDRESS, 16, 2);
NGSerialNotification notificationSerial = NGSerialNotification();
NGCentralUnitControl unitCentral = NGCentralUnitControl(CENTRAL);

enum workMode { wmNone, wmMotionCommand };

workMode _workMode = wmNone;
 
void setup() {
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
    case wmMotionCommand:
      int readed = 0;
      char input[10];
      while (Serial.available()) {
        input[readed] = Serial.read();
        if (input[readed] != '\n') {
          readed++;
        }
      }
      if (readed > 0) {
        char* command = (char*)malloc(readed + 1);
        for (int i = 0; i < readed; i++) {
          command[i] = input[i];
        }
        command[readed] = '\0';
        unitCentral.sendUnitCommand(MOTION, command);
        free(command);
      }
      observeMemory(5000);
      break;
    }
    unitCentral.processingLoop();
}
