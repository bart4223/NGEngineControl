#define ZX81 // DEFAULT, ZX81

#include <NGCommon.h>
#include <NGZX81Font.h>
#include <NGMemoryObserver.h>
#include <NGColorDotMatrix.h>
#include <NGColorDotMatrixCharDigit.h>

#define DELAY 100

NGColorDotMatrix *cdm = new NGColorDotMatrix();
NGColorDotMatrixCharDigit *cdmcd = new NGColorDotMatrixCharDigit(cdm);

#ifdef ZX81
NGZX81Font *fontZX81 = new NGZX81Font();
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
  if (letter > 3) {
    letter = 0;
  }
  switch(letter) {
    case 0:
      cdmcd->setChar('Z');
      break;
    case 1:
      cdmcd->setChar('X');
      break;
    case 2:
      cdmcd->setChar('8');
      break;
    case 3:
      cdmcd->setChar('1');
      break;
  }
}
