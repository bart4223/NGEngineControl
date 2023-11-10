#include <NGMemoryObserver.h>
#include <NGLightSensor.h>

#define DELAY 500
#define LIGHTSENSORBRIGHT    800 // 600
#define LIGHTSENSORBRIGHTID 0x01
#define LIGHTSENSORDARK      600 // 500
#define LIGHTSENSORDARKID   0x02

NGLightSensor ls = NGLightSensor();

byte _lastID = 0x00;

void setup() {
  observeMemory(0);
  //ls.setLogging(true);
  //ls.setLogging(true, DELAY);
  //ls.registerThreshold(650, tlUnder, 4, tvHigh, DELAY);
  ls.registerThreshold(LIGHTSENSORBRIGHT, tlOver, LIGHTSENSORBRIGHTID, &lightSensorCallback, DELAY);
  ls.registerThreshold(LIGHTSENSORDARK, tlUnder, LIGHTSENSORDARKID, &lightSensorCallback, DELAY);
  ls.initialize();
  observeMemory(0);
}

void loop() {
  ls.processingLoop();
  //observeMemory(DELAY);
}

void lightSensorCallback(byte id) {
  if (_lastID != id) {
    Serial.println(id);
    _lastID = id;
  }
}
