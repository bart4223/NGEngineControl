#include <NGEngineControl.h>

NGEngineControl engineBase = NGEngineControl(ENGINE_0);

enum mode { MoveEngineBase, SimulateEngineBase, ReadTransducerBase, ReadTransducerShoulder, ReadTransducerElbow };

const byte transducerBasePin = 3;
const byte transducerShoulderPin = 4;
const byte transducerElbowPin = 5;
const int _lowTransducerBaseRad = 560;
const int _highTransducerBaseRad = 1020;
const int _lowTransducerShoulderRad = 560;
const int _highTransducerShoulderRad = 1020;
const int _lowTransducerElbowRad = 560;
const int _highTransducerElbowRad = 1020;
const int _sleepReadTransducer = 500;
const mode _mode = SimulateEngineBase;
 
void setup() {
  engineBase.initialize();
  Serial.print("Current Mode = ");
  Serial.println(_mode);
  Serial.print("Current Transducer Base Radiant = ");
  Serial.println(analogRead(transducerBasePin));
  Serial.print("Current Transducer Shoulder Radiant = ");
  Serial.println(analogRead(transducerShoulderPin));
  Serial.print("Current Transducer Elbow Radiant = ");
  Serial.println(analogRead(transducerElbowPin));
}

void loop() {
  int radiantTransducerBase = analogRead(transducerBasePin);
  int radiantTransducerShoulder = analogRead(transducerShoulderPin);
  int radiantTransducerElbow = analogRead(transducerElbowPin);
  switch (_mode) {
    case ReadTransducerBase:
      Serial.println(radiantTransducerBase);
      delay(_sleepReadTransducer);
      break;
    case ReadTransducerShoulder:
      Serial.println(radiantTransducerShoulder);
      delay(_sleepReadTransducer);
      break;
    case ReadTransducerElbow:
      Serial.println(radiantTransducerElbow);
      delay(_sleepReadTransducer);
      break;
    case MoveEngineBase:
      Serial.print("Rotate transducer base to Radiant = ");
      while (Serial.available() == 0);
      radiantTransducerBase = Serial.parseInt();
      Serial.read();
      Serial.println(radiantTransducerBase);
      break;
    case SimulateEngineBase:
      if (radiantTransducerBase >= _highTransducerBaseRad - ((_highTransducerBaseRad - _lowTransducerBaseRad) / 2)) {
        radiantTransducerBase = _lowTransducerBaseRad;
      }
      else {
        radiantTransducerBase = _highTransducerBaseRad;
      }
      break;
  }
  if (_mode == MoveEngineBase || _mode == SimulateEngineBase) {
    if (radiantTransducerBase >= _lowTransducerBaseRad && radiantTransducerBase <= _highTransducerBaseRad) {
      Serial.println("Rotation of transducer base start...");
      unsigned long start = millis();
      movingEngineBase(radiantTransducerBase);
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

void movingEngineBase(int targetRad) {
  int currentRad = analogRead(transducerBasePin);
  engineBase.setSpeed(MAXSPEED);
  while (currentRad <= (targetRad - 3) || (targetRad + 3) <= currentRad) {
    if (currentRad < targetRad) {
      engineBase.setLogging(false);
      engineBase.run(BACKWARD);
      engineBase.setLogging(true);
    } else if (currentRad > targetRad) {
      engineBase.setLogging(false);
      engineBase.run(FORWARD);
      engineBase.setLogging(true);
    }
    currentRad = analogRead(transducerBasePin);
    delay(20);
  }
  engineBase.stop();
}
