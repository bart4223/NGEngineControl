#include <NGMemoryObserver.h>
#include <NGLCDNotification.h>
#include <NGSerialNotification.h>
#include <NGCentralUnitControl.h>

#define CENTRAL (char*)"Central"

NGLCDNotification notificationLCD = NGLCDNotification(0x27, 16, 2);
NGSerialNotification notificationSerial = NGSerialNotification();
NGCentralUnitControl unitCentral = NGCentralUnitControl(CENTRAL);

void setup() {
    unitCentral.registerNotification(&notificationLCD);
    unitCentral.registerNotification(&notificationSerial);
    unitCentral.initialize();
}

void loop() {
    observeMemory(5000);
}
