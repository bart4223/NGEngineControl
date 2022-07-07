#define MAXTESTLEVEL 1

#include <NGEngineControl.h>

NGEngineControl engine0 = NGEngineControl(ENGINE_0);

long duration;
int testLevel = 0;
bool beginTest = true;

void setup() {
  engine0.initialize();
}

void loop() {
  if (testLevel <= MAXTESTLEVEL) {
    switch(testLevel) {
      case 0:
        if (beginTest) {
          beginTestLevel();
          engine0.setSpeed(255,3000);
          engine0.run(edForward);
        }
        if ((millis() - duration) >= 6000) {
          engine0.stop(2000);
          endTestLevel(3000);
        }
        break;
      case 1:
        if (beginTest) {
          beginTestLevel();
          engine0.setSpeed(255,3000);
          engine0.run(edBackward);
        }
        if ((millis() - duration) >= 6000) {
          engine0.stop(2000);
          endTestLevel(3000);
        }
        break;
      case 2:
        if (beginTest) {
          beginTestLevel();
          engine0.setSpeed(255);
          engine0.run(edForward);
        }
        if ((millis() - duration) >= 10000) {
          engine0.stop();
          endTestLevel(3000);
        }
        break;
      default:
        char log[100];
        sprintf(log, "==>Test Level %d unknown!", testLevel);
        Serial.println(log);
        testLevel++;
        break;
    }
  } else if (testLevel == MAXTESTLEVEL + 1) {
        Serial.println(">>>Tests finished");
        testLevel++;
  }
}

void beginTestLevel() {
  char log[100];
  sprintf(log, "==< Begin Test Level %d", testLevel);
  Serial.println(log);
  beginTest = false;
  duration = millis();
}

void endTestLevel(int wait) {
  char log[100];
  sprintf(log, ">== End Test Level %d", testLevel);
  Serial.println(log);
  testLevel++;
  beginTest = true;
  if (wait > 0) {
    delay(wait);
  }
}
