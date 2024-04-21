#include <NGCommon.h>
#include <NGZX81Font.h>
#include <NGMemoryObserver.h>
#include <NGColorDotMatrixDecimalDigit.h>

#define DELAY 100

NGColorDotMatrix *cdm = new NGColorDotMatrix();
NGColorDotMatrixDecimalDigit *cdmdd = new NGColorDotMatrixDecimalDigit(cdm);

NGZX81Font *fontZX81 = new NGZX81Font();

#define START 0x09

byte counter = START;
int posx = 0;

void setup() {
  observeMemory(0);
  cdm->initialize();
  //cdmdd->setRandomColorBackground(true);
  //cdmdd->setColorBackground(COLOR_RED);
  //cdmdd->setRandomColor(true);
  cdmdd->setColor(COLOR_GREEN);
  initFont();
  cdmdd->setPosX(posx);
  cdmdd->setValue(counter);
  observeMemory(0);
}

void loop() {
  delay(DELAY);
  posx++;
  cdm->beginUpdate();
  cdm->clear();
  cdmdd->setPosX(posx);
  if (posx == 7) {
    posx = -1;
    if (counter == 0) {
      counter = START;
    } else {
      counter--;
    }
    initFont();
    cdmdd->setValue(counter);
  }
  cdm->endUpdate();
}

void initFont() {
  if (getYesOrNo()) {
    cdmdd->setFont(fontZX81);
  } else {
    cdmdd->setFont(nullptr);
  }
}
