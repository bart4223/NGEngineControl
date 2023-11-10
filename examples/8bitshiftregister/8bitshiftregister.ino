#include <NGCommon.h>
#include <NG8BitShiftRegister.h>

#define SHIFTREGISTERONE
#define SHIFTREGISTERTWO

#ifdef NG_PLATFORM_AVR
#include <NGMemoryObserver.h>
#endif

#ifdef SHIFTREGISTERONE
#define LATCHPINONE  4
#define CLOCKPINONE  5
#define DATAPINONE   3
#endif

#ifdef SHIFTREGISTERTWO
#define LATCHPINTWO  7
#define CLOCKPINTWO  8
#define DATAPINTWO   6
#endif

#define DELAY 1000
//#define RANDOMIZE

#ifdef SHIFTREGISTERONE
NG8BitShiftRegister srOne = NG8BitShiftRegister(LATCHPINONE, CLOCKPINONE, DATAPINONE);
#endif
#ifdef SHIFTREGISTERTWO
NG8BitShiftRegister srTwo = NG8BitShiftRegister(LATCHPINTWO, CLOCKPINTWO, DATAPINTWO);
#endif

void setup() {
  #ifdef SHIFTREGISTERONE
  srOne.initialize();
  #ifdef RANDOMIZE
  srOne.setValue(random(0, 255));
  #else
  srOne.setValue(1);
  #endif
  #endif
  #ifdef SHIFTREGISTERTWO
  srTwo.initialize();
  #ifdef RANDOMIZE
  srTwo.setValue(random(0, 255));
  #else
  srTwo.setValue(1);
  #endif
  #endif
}

void loop() {
  #ifdef NG_PLATFORM_AVR
  observeMemory(DELAY);
  #endif
  #ifdef NG_PLATFORM_ARM
  delay(DELAY);
  #endif
  #ifdef SHIFTREGISTERONE
  if (srOne.getValue() == 128) {
    #ifdef RANDOMIZE
    srOne.setValue(random(0, 255));
    #else
    srOne.setValue(1);
    #endif
  } else {
    srOne.shiftValue();
  }
  #endif
  #ifdef SHIFTREGISTERTWO
  if (srTwo.getValue() == 128) {
    #ifdef RANDOMIZE
    srTwo.setValue(random(0, 255));
    #else
    srTwo.setValue(1);
    #endif
  } else {
    srTwo.shiftValue();
  }
  #endif
}
