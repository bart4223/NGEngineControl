#include <NGMemoryObserver.h>
#include <NGLCDNotification.h>
#include <NGSerialNotification.h>
#include <NGUnitControl.h>

#define MOTION          (char*)"Motion"
#define MOTIONADDRESS   0x09
#define LCDADDRESS      0x27

NGLCDNotification notificationLCD = NGLCDNotification(LCDADDRESS, 16, 2);
NGSerialNotification notificationSerial = NGSerialNotification();
NGUnitControl unitMotion = NGUnitControl(MOTION, MOTIONADDRESS);

enum workMode { wmNone };

workMode _workMode = wmNone;
 
void setup() {
    _unit = &unitMotion;
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
