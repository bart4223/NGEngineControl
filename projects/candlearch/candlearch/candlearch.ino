#define PROD false //false,true

#include <NGCandleArchUnitControl.h>
#if (PROD == false)
#include <NGSerialNotification.h>
#endif

#define _CANDLEARCH "Candle Arch"
#define CANDLEARCH  (char*)_CANDLEARCH

#define HOUSELIGHTINGLATCHPIN   1
#define HOUSELIGHTINGCLOCKPIN   2
#define HOUSELIGHTINGDATAPIN    3
#define FORESTLIGHTINGLATCHPIN  4
#define FORESTLIGHTINGCLOCKPIN  5
#define FORESTLIGHTINGDATAPIN   6
#define TESTSEQUENCEPIN         7

#define TESTSEQUENCEDELAY 3000

NGCandleArchUnitControl unitCandleArch = NGCandleArchUnitControl(CANDLEARCH);
#if (PROD == false)
NGSerialNotification serialNotification = NGSerialNotification();
#endif

byte houseLighting;
byte forestLighting;

void setup() {
  setGlobalUnit(&unitCandleArch);
  #if (PROD != true)
  unitCandleArch.registerNotification(&serialNotification);
  #else
  unitCandleArch.setLogging(false);
  #endif
  houseLighting = unitCandleArch.registerLightingArea(HOUSELIGHTINGLATCHPIN, HOUSELIGHTINGCLOCKPIN, HOUSELIGHTINGDATAPIN);
  forestLighting = unitCandleArch.registerLightingArea(FORESTLIGHTINGLATCHPIN, FORESTLIGHTINGCLOCKPIN, FORESTLIGHTINGDATAPIN);
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
}
