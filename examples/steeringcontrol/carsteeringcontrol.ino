#include <NGSteeringControl.h>
#include <NGCarSteeringControl.h>

#define MAXLOOPS 1

NGCustomSteeringControl *sc = new NGCarSteeringControl();
int index = 0;

void setup() {
  sc->initialize();
}

void loop() {
  if (index < MAXLOOPS) {
    sc->run(edForward, 50);
    delay(1000);
    sc->run(edBackward, 50);
    delay(1000);
    sc->stop();
    index++;
  }
}
