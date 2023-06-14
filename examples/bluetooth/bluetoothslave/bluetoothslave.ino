#include <NGMemoryObserver.h>
#include <NGBluetoothSlave.h>

#define LED 8

NGBluetoothSlave bts = NGBluetoothSlave();

void setup() {
  observeMemory(0);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  bts.registerSwitchCallback(&SwitchCallback);
  bts.setLogging(true);
  bts.initialize();
  observeMemory(0);
}

void loop() {
  bts.processingLoop();
}

void SwitchCallback(byte context, bool on) {
  switch (context) {
    case 0x00:
      if (on) {
        digitalWrite(LED, HIGH);
      } else {
        digitalWrite(LED, LOW);
      }
      break;
  }
}
