#include <NGMemoryObserver.h>
#include <NGTimeOfFlightObjectRecognizer.h>

#define DELAY 500
#define MAXDISTANCE 25

NGTimeOfFlightObjectRecognizer tofor = NGTimeOfFlightObjectRecognizer(MAXDISTANCE);

void setup() {
  observeMemory(0);
  tofor.initialize();
  observeMemory(0);
}

void loop() {
  if (tofor.detected()) {
    Serial.print("contact in ");
    Serial.print(tofor.getCloseness());
    Serial.println(" cm");
  }
  observeMemory(DELAY);
}
