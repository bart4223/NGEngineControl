#include <NGMemoryObserver.h>
#include <NGDigitalPotentiometer.h>

#define ADDRESS_POTI 0x00
#define PIN_CS 53

#define DELAY   250
#define DELAYTWO  5

#define POTI_MAX 230
#define POTI_MIN  80

NGDigitalPotentiometer dp = NGDigitalPotentiometer(PIN_CS, ADDRESS_POTI);

void setup() {
  observeMemory(0);
  dp.initialize();
  observeMemory(0);
}

void loop() {
  for (int i = POTI_MIN; i <= POTI_MAX; i++) {
    dp.setValue(i);
    delay(DELAYTWO);
  }
  delay(DELAY);
  for (int i = POTI_MAX; i >= POTI_MIN; i--) {
    dp.setValue(i);
    delay(DELAYTWO);
  }
}
