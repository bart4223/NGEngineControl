#define PROD true //false,true

#include <NGCandleArchUnitControl.h>
#include <NGLightSensor.h>
#if (PROD == false)
#include <NGSerialNotification.h>
#endif

#define _CANDLEARCH "Candle Arch"
#define CANDLEARCH  (char*)_CANDLEARCH

#define LIGHTSENSORBRIGHT    800
#define LIGHTSENSORBRIGHTID 0x01
#define LIGHTSENSORDARK      600
#define LIGHTSENSORDARKID   0x02
#define LIGHTSENSORDELAY    1000

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
NGLightSensor lightSensor = NGLightSensor();
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
  lightSensor.registerThreshold(LIGHTSENSORBRIGHT, tlOver, LIGHTSENSORBRIGHTID, &lightSensorCallback, LIGHTSENSORDELAY);
  lightSensor.registerThreshold(LIGHTSENSORDARK, tlUnder, LIGHTSENSORDARKID, &lightSensorCallback, LIGHTSENSORDELAY);
  lightSensor.initialize();
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
    while (IsButtonPressed(TESTSEQUENCEPIN)) {
      delay(TESTSEQUENCEDELAY);
    }
    unitCandleArch.testSequenceStop();
    unitCandleArch.writeInfo("Test sequence stopped");
  }
  unitCandleArch.startUp();
  unitCandleArch.clearInfo();
}

void loop() {
  lightSensor.processingLoop();
  unitCandleArch.processingLoop();
  #if (PROD == false)
  testProcedure();
  #endif
}

void lightSensorCallback(byte id) {
  unitCandleArch.setLightSensorData(id);
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
