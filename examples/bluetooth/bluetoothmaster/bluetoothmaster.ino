#include <NGMemoryObserver.h>
#include <NGBluetoothMaster.h>

#define BTN_FIRE 8

NGBluetoothMaster btm = NGBluetoothMaster();
bool button = false;
int btnLastFire;

void setup() {
  observeMemory(0);
  pinMode(BTN_FIRE, INPUT_PULLUP);
  btm.initialize();
  observeMemory(0);
}

void loop() {
  int btnFire = digitalRead(BTN_FIRE);
  if (btnLastFire == HIGH && btnFire == LOW) {
    int counter = 0;
    if (!button) {
      button = true;
      counter = 42;
    } else {
      button = false;
    }
    btm.sendCounterCommand(0x00, counter);
  }
  btnLastFire = btnFire;
}
