#define PROD true //false,true
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

void setup() {
    setGlobalUnit(&unitMotion);
    unitMotion.registerNotification(&notificationSerial);
    #if (PROD == false)
    unitMotion.registerNotification(&notificationLCD);
    #endif
    unitMotion.initialize();
    #if (PROD == false)
    unitMotion.setWorkMode(wmObserveMemory);
    #endif
    unitMotion.clearInfo();
}

void loop() {
    unitMotion.processingLoop();
}
