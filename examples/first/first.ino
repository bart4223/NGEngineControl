#include <NGMemoryObserver.h>

#define LEDPIN   13
#define SLEEP  1000

void setup() {
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
}

void loop() {
  digitalWrite(LEDPIN, HIGH);
  Serial.println("Hello world");
  delay(SLEEP);
  digitalWrite(LEDPIN, LOW);
  observeMemory(SLEEP);
}
