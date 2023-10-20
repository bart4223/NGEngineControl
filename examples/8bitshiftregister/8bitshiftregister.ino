#include <NGMemoryObserver.h>
#include <NG8BitShiftRegister.h>

#define LATCHPIN  7 // 7, 4
#define CLOCKPIN  8 // 8, 5
#define DATAPIN   6 // 6, 3

#define DELAY 1000

NG8BitShiftRegister sr = NG8BitShiftRegister(LATCHPIN, CLOCKPIN, DATAPIN);

void setup() {
  sr.initialize();
  sr.setValue(random(0, 255));
}

void loop() {
  observeMemory(DELAY);
  if (sr.getValue() == 128) {
    sr.setValue(random(0, 255));
  } else {
    sr.shiftValue();
  }
}
