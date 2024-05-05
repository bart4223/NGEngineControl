#include <NGMemoryObserver.h>
#include <NGColorDotMatrixGradientPoint.h>
#include <NGColorDotMatrix.h>

#define DELAY 10
#define GRADIENTSTAGES 10

NGColorDotMatrix *cdm = new NGColorDotMatrix();
NGColorDotMatrixGradientPoint *cdmgpOne = new NGColorDotMatrixGradientPoint(cdm, COLOR_GREEN, GRADIENTSTAGES);
NGColorDotMatrixGradientPoint *cdmgpTwo = new NGColorDotMatrixGradientPoint(cdm, COLOR_RED, GRADIENTSTAGES);

int posX = 3;
int posY = 2;
int gradientX = 0;
int gradientY = 0;
bool animation = true;

void setup() {
  observeMemory(0);
  cdm->initialize();
}

void loop() {
  //delay(DELAY);
  drawPoints();
  if (animation) {
    gradientX++;
    if (gradientX >= GRADIENTSTAGES) {
      clearPoints();
      gradientX = 0;
      posX++;
      if (posX > 7) {
        posX = 0;
      }
      drawPoints();
    }
  }
}

void drawPoints() {
  cdmgpOne->beginUpdate();
  cdmgpTwo->beginUpdate();
  cdmgpOne->setPosition(posX, posY);
  cdmgpOne->setGradient(gradientX, gradientY);
  cdmgpTwo->setPosition(posX, posY + 1);
  cdmgpTwo->setGradient(gradientX, gradientY);
  cdmgpTwo->endUpdate();
  cdmgpOne->endUpdate();
}

void clearPoints() {
  cdmgpOne->clear();
  cdmgpTwo->clear();
}
