#include <NGJingleGorilla.h>
#include <NGJinglePopcorn.h>
#include <NGJingleSuperMario.h>
#include <NGJingleSuperMarioShort.h>
#include <NGJingleHelloDude.h>
#include <NGJingleAlarm.h>
#include <NGJingleThinking.h>
#include <NGJingleBoot.h>
#include <NGJingleBeep.h>
#include <NGJingleJingleBells.h>
#include <NGJingleChristmasSong.h>
#include <NGSoundMachine.h>

NGSoundMachine sm = NGSoundMachine();

void setup()
{
  sm.registerJingle(new NGJingleGorilla);
  sm.registerJingle(new NGJinglePopcorn);
  sm.registerJingle(new NGJingleSuperMario);
  sm.registerJingle(new NGJingleSuperMarioShort);
  sm.registerJingle(new NGJingleHelloDude);
  sm.registerJingle(new NGJingleAlarm);
  sm.registerJingle(new NGJingleThinking);
  sm.registerJingle(new NGJingleBoot);
  sm.registerJingle(new NGJingleBeep);
  sm.registerJingle(new NGJingleJingleBells);
  sm.registerJingle(new NGJingleChristmasSong);
  sm.initialize();
}

void loop()
{
  sm.playRandom();
  delay(500);
}
