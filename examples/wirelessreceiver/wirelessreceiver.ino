#include <NGSimpleWirelessReceiver.h>
#include <NGJingleBeep.h>
#include <NGJingleGorilla.h>
#include <NGJingleSuperMarioShort.h>
#include <NGJingleHelloDude.h>
#include <NGSoundMachine.h>

#define PINONE   7
#define PINTWO   8
#define PINTHREE 9
#define PINFOUR 10
#define DELAY 500

NGSimpleWirelessReceiver swr = NGSimpleWirelessReceiver();
NGSoundMachine sm = NGSoundMachine();
int jingleOne, jingleTwo, jingleThree, jingleFour;

void setup() {
  Serial.begin(9600);
  swr.registerCallback(PINONE, swrmHIGH, &fireOne, DELAY);
  swr.registerCallback(PINTWO, swrmHIGH, &fireTwo, DELAY);
  swr.registerCallback(PINTHREE, swrmHIGH, &fireThree, DELAY);
  swr.registerCallback(PINFOUR, swrmHIGH, &fireFour, DELAY);
  swr.initialize();
  jingleOne = sm.registerJingle(new NGJingleBeep);
  jingleTwo = sm.registerJingle(new NGJingleGorilla);
  jingleThree = sm.registerJingle(new NGJingleSuperMarioShort);
  jingleFour = sm.registerJingle(new NGJingleHelloDude);
  sm.initialize();
}

void loop() {
  swr.processingLoop();
}

void fireOne() {
  Serial.println("Fire One");
  sm.play(jingleOne);
}

void fireTwo() {
  Serial.println("Fire Two");
  sm.play(jingleTwo);
}

void fireThree() {
  Serial.println("Fire Three");
  sm.play(jingleThree);
}

void fireFour() {
  Serial.println("Fire Four");
  sm.play(jingleFour);
}
