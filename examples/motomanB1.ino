#include <NGEngineControl.h>

NGEngineControl engine0 = NGEngineControl(ENGINE_0);

const byte transducerBasePin = 3;
const int _lowRad = 42;
const int _highRad = 600;

void setup() {
  engine0.initialize();
}

void loop() {
  Serial.print("Rotate to Radiant = ");
  while (Serial.available() == 0);
  int radiant = Serial.parseInt();
  Serial.read();
  Serial.println(radiant);
  if (radiant >= _lowRad && radiant <= _highRad) {
    Serial.println("Rotation start...");
    unsigned long start = millis();
    rotate(radiant);
    unsigned long duration = millis() - start;
    Serial.print("...Rotation end (");
    Serial.print("Rad: ");
    Serial.print(analogRead(transducerBasePin));
    Serial.print(", Duration: ");
    Serial.print(duration);
    Serial.println(")");
  } else
    Serial.println("Radiant is invalid");
}

void rotate(int rad) {
  delay(200);
}
