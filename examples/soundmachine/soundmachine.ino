#include <NGMemoryObserver.h>
#include <NGJingleGorilla.h>
#include <NGJinglePopcorn.h>
#include <NGJingleSuperMarioShort.h>
#include <NGJingleHelloDude.h>
#include <NGJingleJingleBells.h>
#include <NGSoundMachine.h>

#define DELAY 500

NGSoundMachine sm = NGSoundMachine();

void setup()
{
  sm.registerJingle(new NGJingleGorilla);
  sm.registerJingle(new NGJinglePopcorn);
  sm.registerJingle(new NGJingleSuperMarioShort);
  sm.registerJingle(new NGJingleHelloDude);
  sm.registerJingle(new NGJingleJingleBells);
  sm.initialize();
}

void loop()
{
  sm.playRandom();
  observeMemory(DELAY);
}
