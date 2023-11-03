#include <NGCommon.h>
#include <NG8BitShiftRegister.h>

#ifdef NG_PLATFORM_AVR
#include <NGMemoryObserver.h>
#endif

#define LATCHPIN  4 // 7, 4
#define CLOCKPIN  5 // 8, 5
#define DATAPIN   3 // 6, 3

#define DELAY 1000
//#define RANDOMIZE

NG8BitShiftRegister sr = NG8BitShiftRegister(LATCHPIN, CLOCKPIN, DATAPIN);

void setup() {
  sr.initialize();
  #ifdef RANDOMIZE
  sr.setValue(random(0, 255));
  #else
  sr.setValue(1);
  #endif
}

void loop() {
  #ifdef NG_PLATFORM_AVR
  observeMemory(DELAY);
  #endif
  #ifdef NG_PLATFORM_ARM
  delay(DELAY);
  #endif
  if (sr.getValue() == 128) {
    #ifdef RANDOMIZE
    sr.setValue(random(0, 255));
    #else
    sr.setValue(1);
    #endif
  } else {
    sr.shiftValue();
  }
}
