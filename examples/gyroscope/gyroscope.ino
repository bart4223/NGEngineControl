#include <NGMemoryObserver.h>
#include <NGGyroscope.h>

#define DELAY 500

NGGyroscope gyro = NGGyroscope();

void setup() {
  gyro.initialize();
  gyro.setThreshold(10,10,10);
}

void loop() {
  bool raised = false;
  gyro.processingLoop();
  if (gyro.isGyroscopeRaisedX()) {
    Serial.print(" X");
    raised = true;
  }
  if (gyro.isGyroscopeRaisedY()) {
    Serial.print(" Y");
    raised = true;
  }
  if (gyro.isGyroscopeRaisedZ()) {
    Serial.print(" Z");
    raised = true;
  }
  if (raised) {
    Serial.println(" raised!");
  }
  observeMemory(DELAY);
}
