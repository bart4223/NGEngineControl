#include <NGMemoryObserver.h>
#include <NGTimeOfFlightObjectRecognizer.h>

#define DELAY 500
#define MAXDISTANCE 25

NGTimeOfFlightObjectRecognizer tofor = NGTimeOfFlightObjectRecognizer(MAXDISTANCE);

void setup() {
  Serial.begin(9600);
  tofor.initialize();
}

void loop() {
  if (tofor.detected()) {
    Serial.print("contact in ");
    Serial.print(tofor.getCloseness());
    Serial.println(" cm");
  }
  observeMemory(DELAY);
}
