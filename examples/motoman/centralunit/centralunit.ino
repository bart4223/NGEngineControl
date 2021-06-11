#include <NGMemoryObserver.h>
#include <NGNotificationSerial.h>
#include <NGCentralUnitControl.h>

#define CENTRAL (char*)"Central"

NGNotificationSerial serialNotification = NGNotificationSerial();
NGCentralUnitControl unitCentral = NGCentralUnitControl(CENTRAL);

void setup() {
    unitCentral.registerNotification(&serialNotification);
    unitCentral.initialize();
}

void loop() {
    observeMemory(5000);
}
