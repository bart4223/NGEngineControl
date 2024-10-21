#include <NGMemoryObserver.h>
#include <NGSimpleKeypad.h>
#include <NGDigitalPotentiometer.h>
#include <NGSoundMachine.h>
#include <NGJingleBeep.h>

#define ADDRESS_POTI 0x00
#define PIN_CS 53

#define KEY1PIN 23
#define KEY1ID  42

#define POTI_MAX 255
#define POTI_MIN 225
#define POTI_STEP  5

#define KEYDELAY 250

NGDigitalPotentiometer dp = NGDigitalPotentiometer(PIN_CS, ADDRESS_POTI);
NGSimpleKeypad skp = NGSimpleKeypad();
NGSoundMachine sm = NGSoundMachine();

void setup() {
  observeMemory(0);
  dp.setMinValue(POTI_MIN);
  dp.setMaxValue(POTI_MAX);
  dp.setStepValue(POTI_STEP);
  dp.initialize(POTI_MAX);
  skp.registerCallback(&SimpleKeypadCallback);
  skp.registerKey(KEY1PIN, KEY1ID, KEYDELAY);
  skp.initialize();
  sm.setConcurrently(true);
  sm.registerJingle(new NGJingleBeep);
  sm.initialize();
  sm.playRandom();
  observeMemory(0);
}

void loop() {
  skp.processingLoop();
  sm.processingLoop();
}

void SimpleKeypadCallback(byte id) {
  switch(id) {
    case KEY1ID:
      dp.changeValue();
      sm.playRandom();
      break;
  }
}
