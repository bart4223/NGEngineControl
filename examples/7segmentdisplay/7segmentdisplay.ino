#include <NGMemoryObserver.h>
#include <NG7SegmentDisplay.h>

#define LATCHPIN  4 // 1, 4
#define CLOCKPIN  5 // 2, 5
#define DATAPIN   6 // 3, 6

#define DELAY 1000

NG7SegmentDisplay sd = NG7SegmentDisplay(LATCHPIN, CLOCKPIN, DATAPIN);

void setup() {
  sd.initialize();
  //sd.setMode(ssmHex);
  sd.setValue(0);
  //sd.setDot();
}

void loop() {
  observeMemory(DELAY);
  //sd.resetDot();
  sd.incrementValue();
  //sd.decrementValue();
}