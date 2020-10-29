#include <NGEngineControl.h>

NGEngineControl engine0 = NGEngineControl(ENGINE_0);

const byte transducerBasePin = 3;
const int _lowRad = 42;
const int _highRad = 600;

void setup() {
  engine0.initialize();
  Serial.print("Current Radiant = ");
  Serial.println(analogRead(transducerBasePin));
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
    Serial.println(" ms)");
  } else
    Serial.println("Radiant is invalid");
}

void rotate(int targetRad) {
  int currentRad = analogRead(transducerBasePin);
  engine0.setSpeed(MAXSPEED);
  while (currentRad <= (targetRad - 3) || (targetRad + 3) <= currentRad) {
    if (currentRad < targetRad) {
      engine0.setLogging(false);
      engine0.run(BACKWARD);
      engine0.setLogging(true);
    } else if (currentRad > targetRad) {
      engine0.setLogging(false);
      engine0.run(FORWARD);
      engine0.setLogging(true);
    }
    currentRad = analogRead(transducerBasePin);
    delay(50);
  }
  engine0.stop();
}
