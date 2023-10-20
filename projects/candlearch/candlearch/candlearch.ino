#define PROD false //false,true

#include <NGCandleArchUnitControl.h>
#if (PROD == false)
#include <NGSerialNotification.h>
#endif

#define _CANDLEARCH "Candle Arch"
#define CANDLEARCH  (char*)_CANDLEARCH

#define HOUSELIGHTINGLATCHPIN   4
#define HOUSELIGHTINGCLOCKPIN   5
#define HOUSELIGHTINGDATAPIN    3
#define FORESTLIGHTINGLATCHPIN  7
#define FORESTLIGHTINGCLOCKPIN  8
#define FORESTLIGHTINGDATAPIN   6
#define TESTSEQUENCEPIN         9

#define TESTSEQUENCEDELAY 3000
#define TESTDELAY         1000

NGCandleArchUnitControl unitCandleArch = NGCandleArchUnitControl(CANDLEARCH);
#if (PROD == false)
NGSerialNotification serialNotification = NGSerialNotification();
#endif

byte houseLightingArea;
byte houseLivingRoomLight;
byte houseFloorLight;
byte forestLightingArea;
byte forestBigTreeLight;
byte forestLittleTreeLight;

void setup() {
  setGlobalUnit(&unitCandleArch);
  #if (PROD != true)
  unitCandleArch.registerNotification(&serialNotification);
  #else
  unitCandleArch.setLogging(false);
  #endif
  houseLightingArea = unitCandleArch.registerLightingArea(HOUSELIGHTINGLATCHPIN, HOUSELIGHTINGCLOCKPIN, HOUSELIGHTINGDATAPIN);
  houseLivingRoomLight = unitCandleArch.registerLight(houseLightingArea);
  houseFloorLight = unitCandleArch.registerLight(houseLightingArea);
  forestLightingArea = unitCandleArch.registerLightingArea(FORESTLIGHTINGLATCHPIN, FORESTLIGHTINGCLOCKPIN, FORESTLIGHTINGDATAPIN);
  forestBigTreeLight = unitCandleArch.registerLight(forestLightingArea);
  forestLittleTreeLight = unitCandleArch.registerLight(forestLightingArea);
  unitCandleArch.initialize();
  #if (PROD == true)
  unitCandleArch.setWorkMode(wmNone);
  #else
  unitCandleArch.setWorkMode(wmObserveMemory);
  #endif
  if (IsButtonPressed(TESTSEQUENCEPIN)) {
    unitCandleArch.testSequenceStart();
    unitCandleArch.writeInfo("Test sequence started", TESTSEQUENCEDELAY);
    unitCandleArch.testSequenceStop();
  }
  unitCandleArch.startUp();
  unitCandleArch.clearInfo();
}

void loop() {
  unitCandleArch.processingLoop();
  #if (PROD == false)
  testProcedure();
  #endif
}

void testProcedure() {
  delay(TESTDELAY);
  unitCandleArch.toogleLight(houseLightingArea, houseLivingRoomLight);
  delay(TESTDELAY);
  unitCandleArch.toogleLight(houseLightingArea, houseFloorLight);
  delay(TESTDELAY);
  unitCandleArch.toogleLight(forestLightingArea, forestBigTreeLight);
  delay(TESTDELAY);
  unitCandleArch.toogleLight(forestLightingArea, forestLittleTreeLight);
}
