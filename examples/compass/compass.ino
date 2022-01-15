#include <NGMemoryObserver.h>
#include <NGCompass.h>

#define DELAY 1000

NGCompass cmp = NGCompass();

void setup() {
  cmp.initialize();
}

void loop() {
  Serial.println(cmp.getDirection());
  observeMemory(DELAY);
}
