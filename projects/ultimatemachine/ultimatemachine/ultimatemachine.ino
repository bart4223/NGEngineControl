#define PROD true //false,true

#include <NGUltimateMachineUnitControl.h>
#if (PROD == false)
#include <NGSerialNotification.h>
#endif

#define _ULTIMATEMACHINE "Ultimate Machine"
#define ULTIMATEMACHINE  (char*)_ULTIMATEMACHINE

#define POWERSWITCHPIN  2
#define FINGERPIN       8

#define FINGERZEROPOS       67
#define FINGERMAXPOS       127
#define FINGERSTEPWIDTH      5

#define DELAY 20

NGUltimateMachineUnitControl unitUltimateMachine = NGUltimateMachineUnitControl(ULTIMATEMACHINE, POWERSWITCHPIN, FINGERPIN, FINGERZEROPOS, FINGERZEROPOS, FINGERMAXPOS, FINGERSTEPWIDTH);
#if (PROD == false)
NGSerialNotification serialNotification = NGSerialNotification();
#endif

void setup() {
  setGlobalUnit(&unitUltimateMachine);
  #if (PROD != true)
  unitUltimateMachine.registerNotification(&serialNotification);
  #else
  unitUltimateMachine.setLogging(false);
  #endif
  unitUltimateMachine.setProcessDelay(DELAY);
  unitUltimateMachine.initialize();
  #if (PROD == true)
  unitUltimateMachine.setWorkMode(wmNone);
  #else
  unitUltimateMachine.setWorkMode(wmObserveMemory);
  #endif
  unitUltimateMachine.startUp();
  unitUltimateMachine.clearInfo();
}

void loop() {
  unitUltimateMachine.processingLoop();
}
