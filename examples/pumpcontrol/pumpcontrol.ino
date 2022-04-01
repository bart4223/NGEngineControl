#include <NGMemoryObserver.h>
#include <NGPumpControl.h>

#define PINPUMP 9
#define DELAY   1000

NGPumpControl pump = NGPumpControl(PINPUMP);

void setup() {
  pump.initialize();
}

void loop() {
  if (pump.isOn()) {
    pump.off();
  } else {
    pump.on();
  }
  observeMemory(DELAY);
}
