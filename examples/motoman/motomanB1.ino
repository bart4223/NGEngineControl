#include <NGEngineControl.h>

NGEngineControl engine0 = NGEngineControl(ENGINE_0);

enum mode { Normal, Simulate, TransducerBase };

const byte transducerBasePin = 3;
const int _lowRad = 570;
const int _highRad = 1020;
const mode _mode = Simulate;
 
void setup() {
  engine0.initialize();
  Serial.print("Current Mode = ");
  Serial.println(_mode);
  Serial.print("Current Transducer Base Radiant = ");
  Serial.println(analogRead(transducerBasePin));
}

void loop() {
  int radiant = analogRead(transducerBasePin);
  switch (_mode) {
    case Normal:
      Serial.print("Rotate transducer base to Radiant = ");
      while (Serial.available() == 0);
      radiant = Serial.parseInt();
      Serial.read();
      Serial.println(radiant);
      break;
    case Simulate:
      if (radiant >= _highRad - ((_highRad - _lowRad) / 2)) {
        radiant = _lowRad;
      }
      else {
        radiant = _highRad;
      }
      break;
    case TransducerBase:
      Serial.println(radiant);
      delay(500);
      break;
  }
  if (_mode == Normal || _mode == Simulate) {
    if (radiant >= _lowRad && radiant <= _highRad) {
      Serial.println("Rotation of transducer base start...");
      unsigned long start = millis();
      rotateTransducerBase(radiant);
      unsigned long duration = millis() - start;
      Serial.print("...Rotation of transducer base end (");
      Serial.print("Rad: ");
      Serial.print(analogRead(transducerBasePin));
      Serial.print(", Duration: ");
      Serial.print(duration);
      Serial.println(" ms)");
    } else
      Serial.println("Radiant of transducer base is invalid");
  }
}

void rotateTransducerBase(int targetRad) {
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
    delay(20);
  }
  engine0.stop();
}
