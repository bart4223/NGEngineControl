#include <NGMemoryObserver.h>
#include <NGSoundMachine.h>
#include <NGSoundMachineEffect.h>
#include <NGJingleSuperMarioShort.h>

#define ACTIVATIONPIN 9

NGSoundMachine *sm = new NGSoundMachine(DEFPINPIEZO, ACTIVATIONPIN);
NGSoundMachineEffect *effect = new NGSoundMachineEffect(sm);

void setup() {
  observeMemory(0);
  sm->setConcurrently(true);
  sm->initialize();
  effect->playJingle(sm->registerJingle(new NGJingleSuperMarioShort));
  effect->initialize();
  sm->activate();
  observeMemory(0);
}

void loop() {
  effect->processingLoop();
}
