#include <NGMemoryObserver.h>
#include <NGColorDotMatrixDecimalDigit.h>

#define DELAY 50

NGColorDotMatrix *cdm = new NGColorDotMatrix();
NGColorDotMatrixDecimalDigit *cdmdd = new NGColorDotMatrixDecimalDigit(cdm);

byte counter = 0x09;
int posx = -1;

void setup() {
  observeMemory(0);
  cdm->initialize();
  //cdmdd->setRandomColorBackground(true);
  //cdmdd->setColorBackground(COLOR_RED);
  //cdmdd->setRandomColor(true);
  cdmdd->setColor(COLOR_GREEN);
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
  if (posx == 8) {
    posx = -1;
    if (counter == 0) {
      counter = 0x09;
    } else {
      counter--;
    }
    cdmdd->setValue(counter);
  }
  cdm->endUpdate();
}
