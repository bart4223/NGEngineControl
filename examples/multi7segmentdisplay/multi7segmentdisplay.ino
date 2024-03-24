#include <NGMemoryObserver.h>
#include <NGMulti7SegmentDisplay.h>

#define CLOCKPIN  5 // 8, 5
#define LATCHPIN  4 // 7, 4
#define DATAPIN   3 // 6, 3

#define DIGITS 2

#define DELAY 200

NGMulti7SegmentDisplay msd = NGMulti7SegmentDisplay(LATCHPIN, CLOCKPIN, DATAPIN, DIGITS);

void setup() {
  msd.initialize();
  //msd.setMode(ssmHex);
  msd.setValue(0);
}

void loop() {
  observeMemory(DELAY);
  msd.incrementValue();
  //msd.decrementValue();
}
