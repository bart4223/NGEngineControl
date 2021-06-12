#include <NGMemoryObserver.h>
#include <NGLCDNotification.h>
#include <NGSerialNotification.h>
#include <NGUnitControl.h>

#define MOTION          (char*)"Motion"
#define MOTIONADDRESS   9

NGLCDNotification notificationLCD = NGLCDNotification(0x27, 16, 2);
NGSerialNotification notificationSerial = NGSerialNotification();
NGUnitControl unitMotion = NGUnitControl(MOTION);

enum workMode { wmNone };

workMode _workMode = wmNone;
 
void setup() {
    unitMotion.registerNotification(&notificationSerial);
    unitMotion.registerNotification(&notificationLCD);
    unitMotion.initialize();
    Serial.print("Current workMode is ");
    Serial.println(_workMode);
}

void loop() {
    switch (_workMode) {
    case wmNone:
      observeMemory(5000);
      break;
    }
    unitMotion.processingLoop();
}
