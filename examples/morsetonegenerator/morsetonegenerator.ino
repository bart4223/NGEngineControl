#include <NGMemoryObserver.h>
#include <NGMorseToneGenerator.h>
#include <NGJingleMorseDit.h>
#include <NGJingleMorseDah.h>
#include <NGJingleMorseBreakLetter.h>
#include <NGJingleMorseBreakWord.h>

#define TEMPO 120
#define DELAY 5000

NGMorseToneGenerator mtg = NGMorseToneGenerator();

void setup() {
  mtg.registerJingleDit(new NGJingleMorseDit);
  mtg.registerJingleDah(new NGJingleMorseDah);
  mtg.registerJingleBreakLetter(new NGJingleMorseBreakLetter);
  mtg.registerJingleBreakWord(new NGJingleMorseBreakWord);
  mtg.setTempo(TEMPO);
  mtg.initialize();
}

void loop() {
  mtg.playSOS();
  observeMemory(DELAY);
}
