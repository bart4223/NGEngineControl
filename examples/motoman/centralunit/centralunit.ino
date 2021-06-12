#include <NGMemoryObserver.h>
#include <NGLCDNotification.h>
#include <NGCentralUnitControl.h>

#define CENTRAL (char*)"Central"

NGLCDNotification notification = NGLCDNotification(0x27, 16, 2);
NGCentralUnitControl unitCentral = NGCentralUnitControl(CENTRAL);

void setup() {
    unitCentral.registerNotification(&notification);
    unitCentral.initialize();
}

void loop() {
    observeMemory(5000);
}
