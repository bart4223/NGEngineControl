#include <NGCommon.h>
#include <NGMemoryObserver.h>
#include <NGColorDotMatrixGradientPoint.h>
#include <NGColorDotMatrix.h>

#define DELAY 10
#define GRADIENTSTAGES 10

NGColorDotMatrix *cdm = new NGColorDotMatrix();
NGColorDotMatrixGradientPoint *cdmgp = new NGColorDotMatrixGradientPoint(cdm, COLOR_GREEN, GRADIENTSTAGES);

enum gradientPointDirection { gpdLeft, gpdRight, gpdUp, gpdDown };

int posX = 3;
int posY = 3;
int gradientX = 0;
int gradientY = 0;
bool animation = true;
bool noDelay = false;
gradientPointDirection direction = gpdRight;

void setup() {
  observeMemory(0);
  setGlobalRandomSeedAnalogInput(A0);
  diceDirection();
  cdm->initialize();
  observeMemory(0);
}

void loop() {
  drawPoint();
  if (animation) {
    int gradient = 0;
    switch(direction) {
      case gpdLeft:
        gradientX--;
        gradient = gradientX;
        break;
      case gpdRight:
        gradientX++;
        gradient = gradientX;
        break;
      case gpdUp:
        gradientY--;
        gradient = gradientY;
        break;
      case gpdDown:
        gradientY++;
        gradient = gradientY;
        break;
    }
    if (abs(gradient) >= GRADIENTSTAGES) {
      clearPoint();
      switch(direction) {
        case gpdLeft:
          gradientX = 0;
          posX--;
          if (posX < 0) {
            posX = 7;
          }
          break;
        case gpdRight:
          gradientX = 0;
          posX++;
          if (posX > 7) {
            posX = 0;
          }
          break;
        case gpdUp:
          gradientY = 0;
          posY--;
          if (posY < 0) {
            posY = 7;
          }
          break;
        case gpdDown:
          gradientY = 0;
          posY++;
          if (posY > 7) {
            posY = 0;
          }
          break;
      }
      drawPoint();
      diceDirection();
      noDelay = true;
    }
    if (!noDelay) {
      delay(DELAY);
    } else {
      noDelay = false;
    }
  }
}

void drawPoint() {
  cdmgp->beginUpdate();
  cdmgp->setPosition(posX, posY);
  cdmgp->setGradient(gradientX, gradientY);
  cdmgp->endUpdate();
}

void clearPoint() {
  cdmgp->clear();
}

void diceDirection() {
  if (getYesOrNo()) {
    switch(random(0, 4)) {
      case 0:
        direction = gpdLeft;
        break;
      case 1:
        direction = gpdRight;
        break;
      case 2:
        direction = gpdUp;
        break;
      case 3:
        direction = gpdDown;
        break;
    }
  }
}
