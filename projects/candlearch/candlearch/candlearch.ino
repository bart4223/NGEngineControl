#define PROD false //false,true

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

byte scenarioOne;
byte scenarioTwo;

void setup() {
  setGlobalUnit(&unitCandleArch);
  #if (PROD != true)
  unitCandleArch.registerNotification(&serialNotification);
  #else
  unitCandleArch.setLogging(false);
  #endif
  // Light Sensor
  lightSensor.registerThreshold(LIGHTSENSORBRIGHT, tlOver, LIGHTSENSORBRIGHTID, &lightSensorCallback, LIGHTSENSORDELAY);
  lightSensor.registerThreshold(LIGHTSENSORDARK, tlUnder, LIGHTSENSORDARKID, &lightSensorCallback, LIGHTSENSORDELAY);
  lightSensor.initialize();
  // Areas and Lights
  byte houseArea = unitCandleArch.registerLightingArea(HOUSELIGHTINGLATCHPIN, HOUSELIGHTINGCLOCKPIN, HOUSELIGHTINGDATAPIN);
  byte houseLivingRoomLight = unitCandleArch.registerLight(houseArea);
  byte houseFloorLight = unitCandleArch.registerLight(houseArea);
  byte houseThreeLight = unitCandleArch.registerLight(houseArea);
  byte houseFourLight = unitCandleArch.registerLight(houseArea);
  byte houseFiveLight = unitCandleArch.registerLight(houseArea);
  byte houseSixLight = unitCandleArch.registerLight(houseArea);
  byte houseSevenLight = unitCandleArch.registerLight(houseArea);
  byte houseEightLight = unitCandleArch.registerLight(houseArea);
  byte forestArea = unitCandleArch.registerLightingArea(FORESTLIGHTINGLATCHPIN, FORESTLIGHTINGCLOCKPIN, FORESTLIGHTINGDATAPIN);
  byte forestBigTreeLight = unitCandleArch.registerLight(forestArea);
  byte forestLittleTreeLight = unitCandleArch.registerLight(forestArea);
  byte forestThreeTreeLight = unitCandleArch.registerLight(forestArea);
  byte forestFourTreeLight = unitCandleArch.registerLight(forestArea);
  byte forestFiveTreeLight = unitCandleArch.registerLight(forestArea);
  byte forestSixTreeLight = unitCandleArch.registerLight(forestArea);
  byte forestSevenTreeLight = unitCandleArch.registerLight(forestArea);
  byte forestEightTreeLight = unitCandleArch.registerLight(forestArea);
  // Scenario One
  scenarioOne = unitCandleArch.registerScenario();
  byte scenarioOneHouseArea = unitCandleArch.registerScenarioArea(scenarioOne, houseArea);
  unitCandleArch.registerScenarioAreaLight(scenarioOne, scenarioOneHouseArea, houseLivingRoomLight);
  unitCandleArch.registerScenarioAreaLight(scenarioOne, scenarioOneHouseArea, houseFloorLight);
  unitCandleArch.registerScenarioAreaLight(scenarioOne, scenarioOneHouseArea, houseThreeLight);
  unitCandleArch.registerScenarioAreaLight(scenarioOne, scenarioOneHouseArea, houseFourLight);
  unitCandleArch.registerScenarioAreaLight(scenarioOne, scenarioOneHouseArea, houseFiveLight);
  unitCandleArch.registerScenarioAreaLight(scenarioOne, scenarioOneHouseArea, houseSixLight);
  unitCandleArch.registerScenarioAreaLight(scenarioOne, scenarioOneHouseArea, houseSevenLight);
  unitCandleArch.registerScenarioAreaLight(scenarioOne, scenarioOneHouseArea, houseEightLight);
  byte scenarioOneForestArea = unitCandleArch.registerScenarioArea(scenarioOne, forestArea);
  unitCandleArch.registerScenarioAreaLight(scenarioOne, scenarioOneForestArea, forestBigTreeLight);
  unitCandleArch.registerScenarioAreaLight(scenarioOne, scenarioOneForestArea, forestLittleTreeLight);
  unitCandleArch.registerScenarioAreaLight(scenarioOne, scenarioOneForestArea, forestThreeTreeLight);
  unitCandleArch.registerScenarioAreaLight(scenarioOne, scenarioOneForestArea, forestFourTreeLight);
  unitCandleArch.registerScenarioAreaLight(scenarioOne, scenarioOneForestArea, forestFiveTreeLight);
  unitCandleArch.registerScenarioAreaLight(scenarioOne, scenarioOneForestArea, forestSixTreeLight);
  unitCandleArch.registerScenarioAreaLight(scenarioOne, scenarioOneForestArea, forestSevenTreeLight);
  unitCandleArch.registerScenarioAreaLight(scenarioOne, scenarioOneForestArea, forestEightTreeLight);
  // Scenario Two
  scenarioTwo = unitCandleArch.registerScenario();
  byte scenarioTwoHouseArea = unitCandleArch.registerScenarioArea(scenarioTwo, houseArea);
  unitCandleArch.registerScenarioAreaLight(scenarioTwo, scenarioTwoHouseArea, houseLivingRoomLight);
  //unitCandleArch.registerScenarioAreaLight(scenarioTwo, scenarioTwoHouseArea, houseFloorLight);
  unitCandleArch.registerScenarioAreaLight(scenarioTwo, scenarioTwoHouseArea, houseThreeLight);
  //unitCandleArch.registerScenarioAreaLight(scenarioTwo, scenarioTwoHouseArea, houseFourLight);
  unitCandleArch.registerScenarioAreaLight(scenarioTwo, scenarioTwoHouseArea, houseFiveLight);
  //unitCandleArch.registerScenarioAreaLight(scenarioTwo, scenarioTwoHouseArea, houseSixLight);
  unitCandleArch.registerScenarioAreaLight(scenarioTwo, scenarioTwoHouseArea, houseSevenLight);
  //unitCandleArch.registerScenarioAreaLight(scenarioTwo, scenarioTwoHouseArea, houseEightLight);
  byte scenarioTwoForestArea = unitCandleArch.registerScenarioArea(scenarioTwo, forestArea);
  unitCandleArch.registerScenarioAreaLight(scenarioTwo, scenarioTwoForestArea, forestBigTreeLight);
  //unitCandleArch.registerScenarioAreaLight(scenarioTwo, scenarioTwoForestArea, forestLittleTreeLight);
  unitCandleArch.registerScenarioAreaLight(scenarioTwo, scenarioTwoForestArea, forestThreeTreeLight);
  //unitCandleArch.registerScenarioAreaLight(scenarioTwo, scenarioTwoForestArea, forestFourTreeLight);
  unitCandleArch.registerScenarioAreaLight(scenarioTwo, scenarioTwoForestArea, forestFiveTreeLight);
  //unitCandleArch.registerScenarioAreaLight(scenarioTwo, scenarioTwoForestArea, forestSixTreeLight);
  unitCandleArch.registerScenarioAreaLight(scenarioTwo, scenarioTwoForestArea, forestSevenTreeLight);
  //unitCandleArch.registerScenarioAreaLight(scenarioTwo, scenarioTwoForestArea, forestEightTreeLight);
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
  unitCandleArch.activateScenario(scenarioOne);
  delay(TESTDELAY);
  unitCandleArch.activateScenario(scenarioTwo);
}
