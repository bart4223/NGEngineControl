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
    if (!button) {
      button = true;
    } else {
      button = false;
    }
    btm.sendSwitchCommand(0x00, button);
  }
  btnLastFire = btnFire;
}
