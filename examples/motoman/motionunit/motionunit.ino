#include <NGMemoryObserver.h>
#include <NGLCDNotification.h>
#include <NGSerialNotification.h>
#include <NGUnitControl.h>

#define MOTION        (char*)"Motion"
#define MOTIONADDRESS 0x21
#define LCDADDRESS    0x27
#define LCDCOLUMNS    16
#define LCDLINES      2

NGLCDNotification notificationLCD = NGLCDNotification(LCDADDRESS, LCDCOLUMNS, LCDLINES);
NGSerialNotification notificationSerial = NGSerialNotification();
NGUnitControl unitMotion = NGUnitControl(MOTION, MOTIONADDRESS);

enum workMode { wmNone, wmObserveMemory };

workMode _workMode = wmNone;
 
void setup() {
    setGlobalUnit(&unitMotion);
    unitMotion.registerNotification(&notificationSerial);
    unitMotion.registerNotification(&notificationLCD);
    unitMotion.initialize();
    Serial.print("Current workMode is ");
    Serial.println(_workMode);
}

void loop() {
    switch (_workMode) {
    case wmNone:
      break;
    case wmObserveMemory:
      observeMemory(5000);
      break;
    }
    unitMotion.processingLoop();
}
