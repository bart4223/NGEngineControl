#include <NGMemoryObserver.h>
#include <NGColorDotMatrixDecimalDigit.h>

#define DELAY 50

NGColorDotMatrix *cdm = new NGColorDotMatrix();
NGColorDotMatrixDecimalDigit *cdmdd = new NGColorDotMatrixDecimalDigit(cdm);

byte counter = 0x00;
int posx = -1;

void setup() {
  observeMemory(0);
  cdm->initialize();
  //cdmdd->setColorBackground(COLOR_RED);
  cdmdd->setColor(COLOR_GREEN);
  cdmdd->setPosX(posx);
  cdmdd->setValue(0);
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
    counter++;
    if (counter > 9) {
      counter = 0x00;
    }
    cdmdd->setValue(counter);
  }
  cdm->endUpdate();
}
