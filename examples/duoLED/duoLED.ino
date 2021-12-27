#include <NGMemoryObserver.h>
#include <NGDuoLED.h>

#define PINLEDONE 10
#define PINLEDTWO 11

#define DELAY 5000

NGDuoLED duoLED = NGDuoLED(PINLEDONE, PINLEDTWO);

void setup() {
  duoLED.initialize();
}

void loop() {
  if (duoLED.isOn()) {
      duoLED.turnOff();
  } else {
    duoLED.turnOn();
  }
  observeMemory(DELAY);
}
