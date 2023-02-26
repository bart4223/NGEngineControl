#include <NGMemoryObserver.h>
#include <NGSimpleKeypad.h>
#include <NGCaterpillarSteeringControl.h>

#define MAINPIN   22
#define MAINID    42
#define RIGHTPIN  23
#define RIGHTID   43
#define LEFTPIN   24
#define LEFTID    44

#define KEYDELAY 500

NGCaterpillarSteeringControl *sc = new NGCaterpillarSteeringControl();
NGSimpleKeypad skp = NGSimpleKeypad();

void setup() {
  observeMemory(0);
  skp.registerCallback(&SimpleKeypadCallback);
  skp.registerKey(MAINPIN, MAINID, KEYDELAY);
  skp.registerKey(RIGHTPIN, RIGHTID, KEYDELAY);
  skp.registerKey(LEFTPIN, LEFTID, KEYDELAY);
  skp.initialize();
  sc->initialize();
  sc->stop();
  observeMemory(0);
}

void loop() {
  skp.processingLoop();
}

void SimpleKeypadCallback(byte id) {
  switch (id) {
    case MAINID:
      if (sc->isRunning()) {
        sc->stop();
      } else {
        sc->runFullSpeedForward();
      }
      break;
    case RIGHTID:
      break;
    case LEFTID:
      break;
  }
  observeMemory(0);
}
