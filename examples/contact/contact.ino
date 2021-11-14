#include <NGContactObjectRecognizer.h>

NGContactObjectRecognizer corLeft = NGContactObjectRecognizer(A2);
NGContactObjectRecognizer corRight = NGContactObjectRecognizer(A3);

void setup() {
  Serial.begin(9600);
  corLeft.initialize();
  corRight.initialize();
}

void loop() {
  if (corLeft.detected()) {
    Serial.println("new contact left");
    delay(100);
  } else if (corLeft.hasDetected()) {
    Serial.println("..still contact left");
  }
  if (corRight.detected()) {
    Serial.println("new contact right");
    delay(100);
  } else if (corRight.hasDetected()) {
    Serial.println("..still contact right");
  }
}
