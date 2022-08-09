#include <NGSimpleWirelessReceiver.h>
#include <NGJingleGorilla.h>
#include <NGSoundMachine.h>

#define PIN0 7
#define DELAY 500

NGSimpleWirelessReceiver swr = NGSimpleWirelessReceiver();
NGSoundMachine sm = NGSoundMachine();
int jingleBeep;

void setup() {
  Serial.begin(9600);
  swr.registerCallback(PIN0, swrmHIGH, &fire, DELAY);
  swr.initialize();
  jingleBeep = sm.registerJingle(new NGJingleGorilla);
  sm.initialize();
}

void loop() {
  swr.processingLoop();
}

void fire() {
  Serial.println("Fire");
  sm.play(jingleBeep);
}
