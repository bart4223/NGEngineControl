#include <NGMemoryObserver.h>
#include <NGSerialNotification.h>
#include <NGCentralUnitControl.h>

#define CENTRAL (char*)"Central"

NGSerialNotification serialNotification = NGSerialNotification();
NGCentralUnitControl unitCentral = NGCentralUnitControl(CENTRAL);

void setup() {
    unitCentral.registerNotification(&serialNotification);
    unitCentral.initialize();
}

void loop() {
    observeMemory(5000);
}
