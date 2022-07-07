#define MAXTESTLEVEL 1

#include <NGEngineControl.h>

NGEngineControl engine0 = NGEngineControl(ENGINE_0);

long duration;
int testLevel = 0;
bool startTest = true;

void setup() {
  engine0.initialize();
  engine0.setSpeed(255,3000);
  duration = millis();
}

void loop() {
  if (testLevel <= MAXTESTLEVEL) {
    switch(testLevel) {
      case 0:
        if (startTest) {
          beginTestLevel();
          engine0.run(edForward);
        }
        if ((millis() - duration) >= 3000) {
          engine0.stop(2000);
          endTestLevel();
        }
        break;
      case 1:
        if (startTest) {
          beginTestLevel();
          engine0.run(edBackward);
        }
        if ((millis() - duration) >= 3000) {
          engine0.stop(2000);
          endTestLevel();
        }
        break;
    }
  }
}

void beginTestLevel() {
  char log[100];
  sprintf(log, "==< Begin Test Level %d", testLevel);
  Serial.println(log);
  startTest = false;
  
}

void endTestLevel() {
  char log[100];
  sprintf(log, ">== End Test Level %d", testLevel);
  Serial.println(log);
  testLevel++;
  startTest = true;
  duration = millis();
}
