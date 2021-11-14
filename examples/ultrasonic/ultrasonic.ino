#include <NGUltrasonicObjectRecognizer.h>

#define PINTRIGGER  10
#define PINECHO     11
#define MAXDISTANCE 15

#define ULTRASONICTIMEOUT 3000

NGUltrasonicObjectRecognizer usor = NGUltrasonicObjectRecognizer(PINTRIGGER, PINECHO, MAXDISTANCE);

void setup() {
  Serial.begin(9600);
  usor.initialize();
}

void loop() {
  if (usor.detected()) {
    Serial.print("contact in ");
    Serial.print(usor.getCloseness());
    Serial.println(" cm");
  }
  delay(200);
}
