#define PROD false //false,true
#include <NGMemoryObserver.h>
#if (PROD == false)
#include <NGLCDNotification.h>
#endif
#include <NGSerialNotification.h>
#include <NGUnitControl.h>

#define _MOTION       "Motion"
#define MOTION        (char*)_MOTION
#define MOTIONADDRESS 0x21
#define LCDADDRESS    0x27
#define LCDCOLUMNS    16
#define LCDLINES      2

#if (PROD == false)
NGLCDNotification notificationLCD = NGLCDNotification(LCDADDRESS, LCDCOLUMNS, LCDLINES);
#endif
NGSerialNotification notificationSerial = NGSerialNotification();
NGUnitControl unitMotion = NGUnitControl(MOTION, MOTIONADDRESS);

enum workMode { wmNone, wmObserveMemory };

workMode _workMode = wmNone;
 
void setup() {
    char log[100];
    setGlobalUnit(&unitMotion);
    unitMotion.registerNotification(&notificationSerial);
    #if (PROD == false)
    unitMotion.registerNotification(&notificationLCD);
    #endif
    unitMotion.initialize();
    unitMotion.clearInfo();
    sprintf(log, "Current workMode is %d", _workMode);
    unitMotion.writeInfo(log);
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
