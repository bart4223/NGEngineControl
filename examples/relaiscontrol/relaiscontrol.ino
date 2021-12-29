#include <NGMemoryObserver.h>
#include <NGRelaisControl.h>

#define PINRELAIS 7
#define DELAY  5000

NGRelaisControl rc = NGRelaisControl(PINRELAIS);

void setup() {
  rc.initialize();
}

void loop() {
  if (rc.isOn()) {
    rc.off();
  } else {
    rc.on();
  }
  observeMemory(DELAY);
}
