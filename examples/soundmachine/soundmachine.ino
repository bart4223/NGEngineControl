#define WITHACTIVATION // NOACTIVATION, WITHACTIVATION

#include <NGMemoryObserver.h>
#include <NGJingleGorilla.h>
#include <NGJinglePopcorn.h>
#include <NGJingleSuperMario.h>
#include <NGJingleSuperMarioShort.h>
#include <NGJingleHelloDude.h>
#include <NGJingleAlarm.h>
#include <NGJingleThinking.h>
#include <NGJingleBoot.h>
#include <NGJingleBeep.h>
#include <NGSoundMachine.h>

#define ACTIVATIONPIN 9

#define DELAY     10000
#define KEEPALIVE   500

#ifdef NOACTIVATION
NGSoundMachine sm = NGSoundMachine();
#endif
#ifdef WITHACTIVATION
NGSoundMachine sm = NGSoundMachine(DEFPINPIEZO, ACTIVATIONPIN);
#endif

long lastPlay = 0;
long lastKeepAlive = 0;

void setup()
{
  observeMemory(0);
  sm.setConcurrently(true);
  sm.registerJingle(new NGJingleSuperMarioShort);
  /*
  sm.registerJingle(new NGJingleGorilla);
  sm.registerJingle(new NGJinglePopcorn);
  sm.registerJingle(new NGJingleSuperMarioShort);
  sm.registerJingle(new NGJingleSuperMario);
  sm.registerJingle(new NGJingleHelloDude);
  sm.registerJingle(new NGJingleAlarm);
  sm.registerJingle(new NGJingleThinking);
  sm.registerJingle(new NGJingleBoot);
  sm.registerJingle(new NGJingleBeep);
  */
  sm.initialize();
  sm.activate();
  observeMemory(0);
}

void loop()
{
  if (millis() - lastPlay > DELAY || lastPlay == 0) {
    Serial.println("Fire sound playing");
    sm.playRandom();
    Serial.println("...done");
    lastPlay = millis();
  }
  sm.processingLoop();
  if (lastKeepAlive == 0 || millis() - lastKeepAlive > KEEPALIVE) {
    Serial.println("Keep alive");
    lastKeepAlive = millis();
  }
}
