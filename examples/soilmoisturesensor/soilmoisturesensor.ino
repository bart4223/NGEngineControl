#include <NGMemoryObserver.h>
#include <NGSoilMoistureSensor.h>

#define PINSENSOR A0
#define DELAY 5000

NGSoilMoistureSensor sms = NGSoilMoistureSensor(PINSENSOR);

void setup() {
  sms.initialize();
}

void loop() {
  char log[100];
  sprintf(log, "%d %", sms.getHumidity());
  Serial.println(log);
  observeMemory(DELAY);
}
