#include <NGMemoryObserver.h>
#include <NGJingleGorilla.h>
#include <NGJinglePopcorn.h>
#include <NGJingleSuperMario.h>
#include <NGJingleSuperMarioShort.h>
#include <NGJingleHelloDude.h>
#include <NGJingleAlarm.h>
#include <NGJingleThinking.h>
#include <NGJingleBoot.h>
#include <NGSoundMachine.h>

#define DELAY     10000
#define KEEPALIVE   500

NGSoundMachine sm = NGSoundMachine();

long lastPlay = 0;
long lastKeepAlive = 0;

void setup()
{
  observeMemory(0);
  sm.setConcurrently(true);
  sm.registerJingle(new NGJingleGorilla);
  sm.registerJingle(new NGJinglePopcorn);
  sm.registerJingle(new NGJingleSuperMario);
  sm.registerJingle(new NGJingleSuperMarioShort);
  sm.registerJingle(new NGJingleHelloDude);
  sm.registerJingle(new NGJingleAlarm);
  sm.registerJingle(new NGJingleThinking);
  sm.registerJingle(new NGJingleBoot);
  sm.initialize();
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
