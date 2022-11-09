#define PROD true //false,true

#include <NGSerialNotification.h>
#include <NGSimpleKeypad.h>
#include <NGBinaryClockUnitControl.h>

#define _BINARYCLOCK  "Clock"
#define BINARYCLOCK   (char*)_BINARYCLOCK

#define KEYDELAY 500

#define KEYCOLOROFFPIN  8
#define KEYCOLOROFFID   1
#define KEYCOLORONPIN   9
#define KEYCOLORONID    2

NGSimpleKeypad simpleKeypad = NGSimpleKeypad();
NGColorDotMatrix cdm = NGColorDotMatrix();
NGBinaryClockUnitControl unitBinaryClock = NGBinaryClockUnitControl(BINARYCLOCK, &cdm);
#if (PROD == false)
NGSerialNotification serialNotification = NGSerialNotification();
#endif

void setup() {
  setGlobalUnit(&unitBinaryClock);
  #if (PROD == false)
  unitBinaryClock.registerNotification(&serialNotification);
  #endif
  unitBinaryClock.setColorOff(COLOR_LIME);
  unitBinaryClock.setColorOn(COLOR_BLUE);
  unitBinaryClock.initialize();
  simpleKeypad.registerCallback(&SimpleKeypadCallback);
  simpleKeypad.registerKey(KEYCOLOROFFPIN, KEYCOLOROFFID, KEYDELAY);
  simpleKeypad.registerKey(KEYCOLORONPIN, KEYCOLORONID, KEYDELAY);
  simpleKeypad.initialize();
  #if (PROD == true)
  unitBinaryClock.setWorkMode(wmNone);
  #else
  unitBinaryClock.setWorkMode(wmObserveMemory);
  #endif
  unitBinaryClock.startUp();
  unitBinaryClock.clearInfo();
}

void loop() {
  simpleKeypad.processingLoop();
  unitBinaryClock.processingLoop();
}

void SimpleKeypadCallback(byte id) {
  Serial.print("Call -> ");
  Serial.println(id);
}
