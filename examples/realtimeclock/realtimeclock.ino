#include <NGMemoryObserver.h>
#include <NGRealTimeClock.h>

#define DELAY 1000

NGRealTimeClock rtc = NGRealTimeClock();

void setup() {
  rtc.initialize();
}

void loop() {
  Serial.println(rtc.getNowAsText());
  Serial.println(rtc.getDateAsText());
  Serial.println(rtc.getTimeAsText());
  observeMemory(DELAY);
}
