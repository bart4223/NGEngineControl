#define ZX81 // DEFAULT, ZX81, C64

#include <NGCommon.h>
#ifdef ZX81
#include <NGZX81Font.h>
#endif
#ifdef C64
#include <NGC64Font.h>
#endif
#include <NGMemoryObserver.h>
#include <NGColorDotMatrix.h>
#include <NGColorDotMatrixCharDigit.h>

#define DELAY 100

NGColorDotMatrix *cdm = new NGColorDotMatrix();
NGColorDotMatrixCharDigit *cdmcd = new NGColorDotMatrixCharDigit(cdm);

#ifdef DEFAULT
#define MAXLETTER 3
#endif
#ifdef ZX81
#define MAXLETTER 3
NGZX81Font *fontZX81 = new NGZX81Font();
#endif
#ifdef C64
#define MAXLETTER 2
NGC64Font *fontC64 = new NGC64Font();
#endif

int posx = 0;
int letter = -1;

void setup() {
  observeMemory(0);
  cdm->initialize();
  //cdmcd->setRandomColorBackground(true);
  //cdmcd->setColorBackground(COLOR_RED);
  //cdmcd->setRandomColor(true);
#ifdef ZX81
  cdmcd->setFont(fontZX81);
#endif
#ifdef C64
  cdmcd->setFont(fontC64);
#endif
  cdmcd->setColor(COLOR_GREEN);
  cdmcd->setPosX(posx);
  initLetter();
  observeMemory(0);
}

void loop() {
  delay(DELAY);
  posx++;
  cdm->beginUpdate();
  cdm->clear();
  cdmcd->setPosX(posx);
  if (posx == 7) {
    posx = -1;
    initLetter();
  }
  cdm->endUpdate();
}

void initLetter() {
  letter++;
  if (letter > MAXLETTER) {
    letter = 0;
  }
  switch(letter) {
    case 0:
      #ifdef ZX81
      cdmcd->setChar('Z');
      #endif
      #ifdef C64
      cdmcd->setChar('C');
      #endif
      break;
    case 1:
      #ifdef ZX81
      cdmcd->setChar('X');
      #endif
      #ifdef C64
      cdmcd->setChar('6');
      #endif
      break;
    case 2:
      #ifdef ZX81
      cdmcd->setChar('8');
      #endif
      #ifdef C64
      cdmcd->setChar('4');
      #endif
      break;
    case 3:
      #ifdef ZX81
      cdmcd->setChar('1');
      #endif
      break;
  }
}
