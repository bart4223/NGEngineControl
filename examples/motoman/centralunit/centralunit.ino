#include <NGMemoryObserver.h>
#include <NGLCDNotification.h>
#include <NGSerialNotification.h>
#include <NGCentralUnitControl.h>

#define CENTRAL     (char*)"Central"
#define TOOL        (char*)"Tool"
#define TOOLADDRESS 8

NGLCDNotification notificationLCD = NGLCDNotification(0x27, 16, 2);
NGSerialNotification notificationSerial = NGSerialNotification();
NGCentralUnitControl unitCentral = NGCentralUnitControl(CENTRAL);

enum workMode { wmNone, wmToolCommand };

workMode _workMode = wmNone;
 
void setup() {
    unitCentral.registerNotification(&notificationSerial);
    unitCentral.registerNotification(&notificationLCD);
    unitCentral.registerUnit(TOOL, TOOLADDRESS);
    unitCentral.initialize();
}

void loop() {
    switch (_workMode) {
    case wmNone:
      observeMemory(5000);
      break;
    case wmToolCommand:
      int readed = 0;
      char input[10];
      while (Serial.available()) {
        input[readed] = Serial.read();
        if (input[readed] != '\n') {
          readed++;
        }
      }
      if (readed > 0) {
        int index = 0;
        char* command = (char*)malloc(readed);
        for (index = 0; index < readed; index++) {
          command[index] = input[index];
        }
        command[index + 1] = '\0';
        unitCentral.sendUnitCommand(TOOL, command);
        free(command);
      }
      observeMemory(5000);
      break;
    }
}
